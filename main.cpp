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

        switch (choice) {r/include/c++/15/cstdlib:46:28: error: ‘#include’ nested depth 200 exceeds maximum of 200 (use ‘-fmax-include-depth=DEPTH’ to increase the maximum)
   46 | #include <bits/c++config.h>
      |                            ^
In file included from include/World.hpp:5:
/usr/include/c++/15/ctime:46:28: error: ‘#include’ nested depth 200 exceeds maximum of 200 (use ‘-fmax-include-depth=DEPTH’ to increase the maximum)
   46 | #include <bits/c++config.h>
      |                            ^
/usr/include/c++/15/ctime:47:18: error: ‘#include’ nested depth 200 exceeds maximum of 200 (use ‘-fmax-include-depth=DEPTH’ to increase the maximum)
   47 | #include <time.h>
      |                  ^
src/Game.cpp:2:10: fatal error: SaveSystem.hpp: No such file or directory
    2 | #include "SaveSystem.hpp"
      |          ^~~~~~~~~~~~~~~~
compilation terminated.

 ✘  Thu 17 Jul - 23:56  ~/Desktop/VoidRoot   origin ☊ main ✔ 
 @psi  

 ✘  Thu 17 Jul - 23:56  ~/Desktop/VoidRoot   origin ☊ main ✔ 
 @psi  
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
