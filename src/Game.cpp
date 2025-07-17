#include "Game.hpp"
#include "SaveSystem.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

Game::Game() {
    player = nullptr;
    inventory = new Inventory();
    std::srand(std::time(nullptr)); // Seed random
}

Game::~Game() {
    delete player;
    delete inventory;
}

void Game::startNewGame() {
    std::string name;
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);

    player = new Player(name);
    currentLocation = World::getRandomLocation();
    std::cout << "\nYou wake up in the " << currentLocation << ".\n";

    gameLoop();
}

bool Game::loadGame() {
    player = SaveSystem::loadPlayer();
    currentLocation = SaveSystem::loadLocation();
    inventory = SaveSystem::loadInventory();

    if (!player) {
        std::cout << "No save found.\n";
        return false;
    }

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
    std::cout << "Game saved!\n";
}

void Game::gameLoop() {
    while (true) {
        std::cout << "\n--- Game Menu ---\n";
        std::cout << "1. Look around\n";
        std::cout << "2. Wander\n";
        std::cout << "3. Search for loot\n";
        std::cout << "4. Inventory\n";
        std::cout << "5. Save and Exit\n";
        std::cout << "Choice: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                std::cout << "You're in " << currentLocation << ". It's quiet...\n";
                break;
            case 2:
                currentLocation = World::getRandomLocation();
                std::cout << "You wander and arrive at the " << currentLocation << ".\n";
                break;
            case 3:
                inventory->addItem("Healing Potion");
                std::cout << "You found a Healing Potion!\n";
                break;
            case 4:
                inventory->show();
                break;
            case 5:
                saveGame();
                return;
            default:
                std::cout << "Invalid input.\n";
        }
    }
}
