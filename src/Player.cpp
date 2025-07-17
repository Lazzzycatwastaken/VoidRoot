#include "../include/Player.hpp"
#include <iostream>

Player::Player(const std::string& name)
    : name(name), characterClass("None"), currentLocation("Wilderness"), health(100), level(1), xp(0), xpToLevelUp(50) {}

void Player::takeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}

void Player::heal(int amount) {
    health += amount;
    if (health > 100) health = 100;
}

void Player::gainXP(int amount) {
    xp += amount;
    while (xp >= xpToLevelUp) {
        xp -= xpToLevelUp;
        levelUp();
    }
}

void Player::levelUp() {
    level++;
    health = 100;
    xpToLevelUp += 25;
    std::cout << "\n>> You leveled up to level " << level << "! Health restored.\n";
}

void Player::setClass(const std::string& newClass) {
    characterClass = newClass;
}

void Player::setHealth(int hp) {
    health = hp;
    if (health > 100) health = 100;
    if (health < 0) health = 0;
}

void Player::setLevel(int lvl) {
    level = (lvl < 1) ? 1 : lvl;
}

void Player::setXP(int newXP) {
    xp = (newXP < 0) ? 0 : newXP;
}

std::string Player::getName() const {
    return name;
}

std::string Player::getClass() const {
    return characterClass;
}

int Player::getLevel() const {
    return level;
}

int Player::getHealth() const {
    return health;
}

int Player::getXP() const {
    return xp;
}

void Player::displayStatus() const {
    std::cout << "\n=== PLAYER STATUS ===\n";
    std::cout << "Name   : " << name << '\n';
    std::cout << "Class  : " << characterClass << '\n';
    std::cout << "Level  : " << level << '\n';
    std::cout << "XP     : " << xp << " / " << xpToLevelUp << '\n';
    std::cout << "Health : " << health << " / 100\n";
    std::cout << "======================\n";
}
