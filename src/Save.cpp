#include "../include/Save.hpp"
#include <fstream>
#include <iostream>

bool saveGame(const Player& player, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open save file for writing.\n";
        return false;
    }

    outFile << player.getName() << '\n';
    outFile << player.getClass() << '\n';
    outFile << player.getHealth() << '\n';
    outFile << player.getLevel() << '\n';
    outFile << player.getXP() << '\n';

    outFile.close();
    return true;
}

bool loadGame(Player& player, const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Failed to open save file for reading.\n";
        return false;
    }

    std::string name, characterClass;
    int health, level, xp;

    std::getline(inFile, name);
    std::getline(inFile, characterClass);
    inFile >> health >> level >> xp;

    player = Player(name);
    player.setClass(characterClass);

    player.setHealth(health);
    player.setLevel(level);
    player.setXP(xp);

    inFile.close();
    return true;
}
