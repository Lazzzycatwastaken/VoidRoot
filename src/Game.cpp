#include "../include/Game.hpp"
#include "SaveSystem.hpp"
#include "World.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>  // for std::find
#include <iomanip>
#include <thread>
#include <chrono>
#include <termios.h>
#include <unistd.h>

Game::Game() {
    player = nullptr;
    inventory = new Inventory();
    std::srand(std::time(nullptr)); // Seed random
}

Game::~Game() {
    delete player;
    delete inventory;
}

termios orig_term;

void disableInputBuffering() {
    tcgetattr(STDIN_FILENO, &orig_term);
    struct termios newt;
    tcgetattr(STDIN_FILENO, &newt);
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void restoreInputBuffering() {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_term);
}

void loading(int seconds, const std::string& message) {
    std::cout << message << " ";
    const char spinner[] = {'|', '/', '-', '\\'};
    int totalFrames = seconds * 10;
    disableInputBuffering();

    for (int i = 0; i < totalFrames; ++i) {
        std::cout << "\b" << spinner[i % 4] << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    restoreInputBuffering();
    std::cout << "\b \n"; //cleanup
}

void Game::startNewGame() {
    std::string name;
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);

    player = new Player(name);
    currentLocation = World::getRandomLocation();

    visitedLocations.clear();
    visitedLocations.push_back(currentLocation);

    loading(2, "Starting new game ");

    std::cout << "\nYou wake up in the " << currentLocation << ".\n";

    gameLoop();
}

bool Game::loadGame() {
    player = SaveSystem::loadPlayer();
    currentLocation = SaveSystem::loadLocation();
    inventory = SaveSystem::loadInventory();

    visitedLocations = SaveSystem::loadVisitedLocations();

    if (!player) {
        std::cout << "No save found.\n";
        return false;
    }
    loading(2, "Loading game ");
    std::cout << "Game loaded! Welcome back, " << player->getName() << ".\n";
    return true;
}

void Game::play() {
    gameLoop();
}

void Game::saveGame() {
    SaveSystem::savePlayer(*player);
    SaveSystem::saveLocation(currentLocation);
    SaveSystem::saveInventory(*inventory);
    SaveSystem::saveVisitedLocations(visitedLocations);

    std::cout << "Game saved!\n";
}

void Game::gameLoop() {
    while (true) {
        // Clear the screen (ANSI escape sequence)
        std::cout << "\033[2J\033[H";

        // Print the game menu (left side)
        std::cout << "--- Game Menu ---\n";
        std::cout << "1. Look around\n";
        std::cout << "2. Wander\n";
        std::cout << "3. Travel\n";
        std::cout << "4. Search for loot\n";
        std::cout << "5. Inventory\n";
        std::cout << "6. Save and Exit\n";

        // Print stats box (right side)
        if (player) {
            printStatsBox(*player);
        }

        // Prompt for user input (cursor moved by printStatsBox)
        std::cout << "Choice: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                std::cout << "You're in " << currentLocation << ". It's quiet...\n";
                break;

            case 2: {
                loading(10, "Wandering ");
                std::string newLoc = World::getRandomLocation();
                currentLocation = newLoc;

                if (std::find(visitedLocations.begin(), visitedLocations.end(), newLoc) == visitedLocations.end()) {
                    visitedLocations.push_back(newLoc);
                }

                std::cout << "You wander and arrive at the " << currentLocation << ".\n";
                break;
            }

            case 3: {
                std::vector<std::string> travelOptions;
                for (const auto& loc : visitedLocations) {
                    if (loc != currentLocation) {
                        travelOptions.push_back(loc);
                    }
                }

                if (travelOptions.empty()) {
                    std::cout << "No other visited locations to travel to.\n";
                    break;
                }

                std::cout << "\nWhere do you want to travel?\n";
                for (size_t i = 0; i < travelOptions.size(); ++i) {
                    std::cout << (i + 1) << ". " << travelOptions[i] << '\n';
                }
                std::cout << "Choice: ";

                int travelChoice;
                std::cin >> travelChoice;
                std::cin.ignore();

                if (travelChoice < 1 || travelChoice > static_cast<int>(travelOptions.size())) {
                    std::cout << "Invalid choice.\n";
                    break;
                }
                
                loading(5, "Travelling ");

                currentLocation = travelOptions[travelChoice - 1];
                std::cout << "You travel to the " << currentLocation << ".\n";
                break;
            }

            case 4:
                loading(5, "Searching for loot ");
                inventory->addItem("Healing Potion");
                std::cout << "You found a Healing Potion!\n";
                break;

            case 5:
                inventory->show();
                break;

            case 6:
                saveGame();
                return;

            default:
                std::cout << "Invalid input.\n";
        }

        std::cout << "\nPress Enter to continue...";
        std::cin.ignore();
    }
}

void Game::printStatsBox(const Player& player) {
    int boxWidth = 30;
    int startCol = 50;

    auto moveCursor = [](int line, int col) {
        std::cout << "\033[" << line << ";" << col << "H";
    };

    int line = 1;

    // Top border
    moveCursor(line++, startCol);
    std::cout << "+" << std::string(boxWidth - 2, '-') << "+";

    // Title
    moveCursor(line++, startCol);
    std::cout << "| Player Stats           |";

    // Separator
    moveCursor(line++, startCol);
    std::cout << "+" << std::string(boxWidth - 2, '-') << "+";

    // Name
    moveCursor(line++, startCol);
    std::cout << "| Name   : " << std::setw(boxWidth - 11) << std::left << player.getName() << "|";

    // Class
    moveCursor(line++, startCol);
    std::cout << "| Class  : " << std::setw(boxWidth - 11) << std::left << player.getClass() << "|";

    // Level
    moveCursor(line++, startCol);
    std::cout << "| Level  : " << std::setw(boxWidth - 11) << std::left << player.getLevel() << "|";

    // Health
    moveCursor(line++, startCol);
    std::cout << "| Health : " << std::setw(boxWidth - 11) << std::left
              << (std::to_string(player.getHealth()) + " / 100") << "|";

    // XP
    moveCursor(line++, startCol);
    std::cout << "| XP     : " << std::setw(boxWidth - 11) << std::left
              << (std::to_string(player.getXP()) + " / ???") << "|";

    // Bottom border
    moveCursor(line++, startCol);
    std::cout << "+" << std::string(boxWidth - 2, '-') << "+";

    // Move cursor to line 15, column 1 to restore input position
    moveCursor(15, 1);
}