#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

class Player {
private:
    std::string name;
    std::string characterClass;
    std::string currentLocation;
    int health;
    int level;
    int xp;
    int xpToLevelUp;

public:
    Player(const std::string& name);

    void takeDamage(int amount);
    void heal(int amount);
    void gainXP(int amount);
    void levelUp();

    void setClass(const std::string& newClass);
    void setHealth(int hp);
    void setLevel(int lvl);
    void setXP(int newXP);

    std::string getName() const;
    std::string getClass() const;
    int getLevel() const;
    int getHealth() const;
    int getXP() const;

    void displayStatus() const;
};

#endif // PLAYER_HPP
