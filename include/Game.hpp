#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <vector>
#include "Player.hpp"
#include "Inventory.hpp"

class Game {
private:
    Player* player;
    Inventory* inventory;
    std::string currentLocation;
    std::vector<std::string> visitedLocations;

    void printStatsBox(const Player& player);

public:
    Game();
    ~Game();

    void startNewGame();
    bool loadGame();
    void play();
    void saveGame();
    void gameLoop();
};

#endif // GAME_HPP
