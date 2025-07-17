#include "Game.hpp"
#include <iostream>

void printMainMenu() {
    std::cout << "\n== TERMINAL RPG ==\n";
    std::cout << "1. Start New Game\n";
    std::cout << "2. Load Game\n";
    std::cout << "3. Exit\n";
    std::cout << "Choose an option: ";
}

int main() {
    int choice;

    while (true) {
        printMainMenu();
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: {
                Game game;
                game.startNewGame();
                break;
            }
            case 2: {
                Game game;
                if (game.loadGame()) {
                    game.play();
                }
                break;
            }
            case 3:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice.\n";
        }
    }

    return 0;
}
