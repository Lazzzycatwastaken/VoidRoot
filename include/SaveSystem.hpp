#ifndef SAVESYSTEM_HPP
#define SAVESYSTEM_HPP

#include <string>
#include <vector>
#include "Player.hpp"
#include "Inventory.hpp"

class SaveSystem {
public:
    static void savePlayer(const Player& player);
    static Player* loadPlayer();

    static void saveInventory(const Inventory& inventory);
    static Inventory* loadInventory();

    static void saveLocation(const std::string& location);
    static std::string loadLocation();

    // Add these declarations:
    static void saveVisitedLocations(const std::vector<std::string>& locations);
    static std::vector<std::string> loadVisitedLocations();
};

#endif // SAVESYSTEM_HPP
