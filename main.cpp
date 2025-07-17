#include <iostream>
#include "Game.hpp"
#include <limits>  // For std::numeric_limits

void printMainMenu() {
    std::cout << "\n== TERMINAL RPG ==\n";
    std::cout << "1. Start New Game\n";
    std::cout << "2. Load Game\n";
    std::cout << "3. Exit\n";
    std::cout << "Choose an option: ";
}

void waitForEnter() {
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    while (true) {
        printMainMenu();

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear(); // clear error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input

            std::cout << "Invalid input. Please enter a number.\n";
            waitForEnter();  // Wait for user to press Enter so message doesn't fly by
            continue; // re-show menu
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush extra input after number

        Game game;

        switch (choice) {
            case 1:
                game.startNewGame();
                break;
            case 2:
                if (game.loadGame()) {
                    game.play();
                }
                break;
            case 3:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice.\n";
                waitForEnter();  // Wait before re-showing menu
        }
    }
}
