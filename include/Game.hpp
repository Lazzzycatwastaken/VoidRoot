#include "Player.hpp"
#include "World.hpp"
#include "Inventory.hpp"

class Game {
private:
    Player* player;
    Inventory* inventory;
    std::string currentLocation;

public:
    Game();
    ~Game();
    void startNewGame();
    bool loadGame();
    void play();
    void saveGame();
    void gameLoop();
};
