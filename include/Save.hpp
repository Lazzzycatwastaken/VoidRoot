#ifndef SAVE_HPP
#define SAVE_HPP

#include "../include/Player.hpp"

bool saveGame(const Player& player, const std::string& filename);
bool loadGame(Player& player, const std::string& filename);

#endif
