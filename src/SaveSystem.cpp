#include "SaveSystem.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>  // C++17 feature

namespace fs = std::filesystem;

void ensureSavesDirectoryExists() {
    const fs::path saveDir("saves");
    if (!fs::exists(saveDir)) {
        if (!fs::create_directory(saveDir)) {
            std::cerr << "Error: Could not create saves directory.\n";
        }
    }
}

void SaveSystem::savePlayer(const Player& player) {
    ensureSavesDirectoryExists();

    std::ofstream file("saves/save_player.txt");
    if (!file) {
        std::cerr << "Error saving player data.\n";
        return;
    }

    file << player.getName() << '\n';
    file << player.getClass() << '\n';
    file << player.getLevel() << '\n';
    file << player.getHealth() << '\n';
    file << player.getXP() << '\n';

    file.close();
}

Player* SaveSystem::loadPlayer() {
    std::ifstream file("saves/save_player.txt");
    if (!file) {
        std::cout << "No player save file found.\n";
        return nullptr;
    }

    std::string name, characterClass;
    int level, health, xp;

    std::getline(file, name);
    std::getline(file, characterClass);
    file >> level >> health >> xp;

    file.close();

    Player* player = new Player(name);
    player->setClass(characterClass);
    player->setLevel(level);
    player->setHealth(health);
    player->setXP(xp);

    return player;
}

void SaveSystem::saveInventory(const Inventory& inventory) {
    ensureSavesDirectoryExists();

    std::ofstream file("saves/save_inventory.txt");
    if (!file) {
        std::cerr << "Error saving inventory data.\n";
        return;
    }

    inventory.saveToFile(file);

    file.close();
}

Inventory* SaveSystem::loadInventory() {
    std::ifstream file("saves/save_inventory.txt");
    if (!file) {
        std::cout << "No inventory save file found.\n";
        return new Inventory();
    }

    Inventory* inventory = new Inventory();
    inventory->loadFromFile(file);

    file.close();

    return inventory;
}

void SaveSystem::saveLocation(const std::string& location) {
    ensureSavesDirectoryExists();

    std::ofstream file("saves/save_location.txt");
    if (!file) {
        std::cerr << "Error saving location data.\n";
        return;
    }
    file << location;
    file.close();
}

std::string SaveSystem::loadLocation() {
    std::ifstream file("saves/save_location.txt");
    if (!file) {
        std::cout << "No location save file found.\n";
        return "Unknown";
    }
    std::string location;
    std::getline(file, location);
    file.close();
    return location;
}

void SaveSystem::saveVisitedLocations(const std::vector<std::string>& locations) {
    ensureSavesDirectoryExists();

    std::ofstream outFile("saves/visited_locations.txt");
    if (!outFile) {
        std::cerr << "Error saving visited locations.\n";
        return;
    }
    for (const auto& loc : locations) {
        outFile << loc << '\n';
    }
}

std::vector<std::string> SaveSystem::loadVisitedLocations() {
    std::vector<std::string> locations;
    std::ifstream inFile("saves/visited_locations.txt");
    if (!inFile) {
        // No visited locations saved yet, return empty vector
        return locations;
    }
    std::string line;
    while (std::getline(inFile, line)) {
        if (!line.empty()) {
            locations.push_back(line);
        }
    }
    return locations;
}
