#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <limits> // For std::numeric_limits
#include "include/Player.hpp"
#include "include/Save.hpp"
#include "include/Location.hpp"
#include "include/TerminalUtils.hpp"

bool gameRunning = true;

std::vector<Location> createLocations() {
    return {
        Location("Forest", "A dense forest with towering trees. The air is thick with the scent of pine."),
        Location("Cave", "A dark cave mouth leads into the mountain. Strange echoes emanate from within."),
        Location("Meadow", "A peaceful meadow filled with wildflowers. A gentle breeze carries their scent."),
        Location("Ruins", "Ancient stone ruins rise from the earth. Their purpose long forgotten."),
        Location("River", "A swift river cuts through the landscape. The water looks clean and refreshing.")
    };
}

void showGameMenu() {
    std::cout << "\n=== ACTIONS ===\n";
    std::cout << "1. Wander to new location" << std::endl;
    std::cout << "2. Look around" << std::endl;
    std::cout << "3. Save game" << std::endl;
    std::cout << "4. Exit" << std::endl;
}

void startGameMenu() {
    std::cout << "=== VOIDROOT ===\n" << std::endl;
    std::cout << "1. Start New Game" << std::endl;
    std::cout << "2. Load Game" << std::endl;
    std::cout << "3. Exit" << std::endl;
}



void gameLoop() {
    Player player("NoName");
    const std::string saveFile = "savegame.txt";
    std::vector<Location> locations = createLocations();
    Location& currentLoc = locations[0];
    std::random_device rd;
    std::mt19937 gen(rd());

    while (gameRunning) {
        startGameMenu();
        int choice;
        int termWidth, termHeight;
        TerminalUtils::wizsize(termWidth, termHeight);
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            std::string name;
            std::cout << "Enter your name: ";
            std::getline(std::cin, name);
            player = Player(name);

            // Start in a random location
            std::uniform_int_distribution<> dis(0, locations.size() - 1);
            int startLoc = dis(gen);
            Location& currentLoc = locations[startLoc];
            std::cout << "\nYou find yourself in the " << currentLoc.getName() << ".\n";
            currentLoc.lookAround();

            bool exploring = true;
            while (exploring && gameRunning) {
                TerminalUtils::clearScreen();  // Clear the entire screen
                TerminalUtils::setCursorPosition(0, 0);  // Move to top-left
                displayStatsBox(player, currentLoc);  // Draw stats box
                
                // Show the game content
                TerminalUtils::setCursorPosition(0, 0);
                showGameMenu();
                
                // Get user input from the bottom
                TerminalUtils::setCursorPosition(0, 10);  // Move cursor below menu
                std::cout << "Enter your choice: ";
                std::cin >> choice;
                std::cin.ignore();

                if (choice == 1) {
                    std::cout << "\nAvailable locations:\n";
                    for (size_t i = 0; i < locations.size(); ++i) {
                        std::cout << i + 1 << ". " << locations[i].getName() << std::endl;
                    }
                    
                    int locChoice;
                    std::cout << "Where would you like to go? ";
                    std::cin >> locChoice;
                    std::cin.ignore();
                    
                    if (locChoice > 0 && locChoice <= static_cast<int>(locations.size())) {
                        currentLoc = locations[locChoice - 1];
                        std::cout << "\nYou travel to the " << currentLoc.getName() << ".\n";
                        currentLoc.lookAround();
                    } else {
                        std::cout << "Invalid location.\n";
                    }
                }
                else if (choice == 2) {
                    currentLoc.lookAround();
                }
                else if (choice == 3) {
                    saveGame(player, saveFile);
                    std::cout << "Game saved successfully.\n";
                }
                else if (choice == 4) {
                    exploring = false;
                    gameRunning = false;
                }
                else {
                    std::cout << "Invalid choice. Please try again.\n";
                }
            }
        }
        else if (choice == 2) {
            if (loadGame(player, saveFile)) {
                TerminalUtils::clearScreen();
                std::cout << "Game loaded successfully.\n";
                displayStatsBox(player, currentLoc);
                player.displayStatus();
            } else {
                std::cout << "No save found, please start a new game.\n";
            }
        }
        else if (choice == 3) {
            std::cout << "Exiting the game." << std::endl;
            gameRunning = false;
        }
        else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}

void displayStatsBox(const Player& player, const Location& currentLoc) {
    int termWidth, termHeight;
    TerminalUtils::wizsize(termWidth, termHeight);
    
    // Calculate stats box position and size
    int boxWidth = 30;  // Width of our stats box
    int boxHeight = 10; // Height of our stats box
    int boxX = termWidth - boxWidth - 1; // Position from right side
    int boxY = 1; // Position from top
    
    // Draw the box with title
    TerminalUtils::drawBox(boxX, boxY, boxWidth, boxHeight, "=== PLAYER INFO ===");
    
    // Display stats inside the box
    TerminalUtils::setCursorPosition(boxX + 2, boxY + 2);
    std::cout << "Name   : " << player.getName();
    TerminalUtils::setCursorPosition(boxX + 2, boxY + 3);
    std::cout << "Class  : " << player.getClass();
    TerminalUtils::setCursorPosition(boxX + 2, boxY + 4);
    std::cout << "Level  : " << player.getLevel();
    TerminalUtils::setCursorPosition(boxX + 2, boxY + 5);
    std::cout << "Health : " << player.getHealth() << "/100";
    TerminalUtils::setCursorPosition(boxX + 2, boxY + 6);
    std::cout << "XP     : " << player.getXP();
    TerminalUtils::setCursorPosition(boxX + 2, boxY + 8);
    std::cout << "Location: " << currentLoc.getName();
    std::cout.flush();  // Add this at the end of displayStatsBox
}

int getValidInput(int min, int max) {
    int choice;
    while (true) {
        std::cout << "Enter your choice: ";
        if (std::cin >> choice && choice >= min && choice <= max) {
            // Valid input
            return choice;
        } else {
            // Invalid input
            std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
            std::cin.clear(); // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Flush the input buffer
        }
    }
}

int main() {
    gameLoop();
    return 0;
}