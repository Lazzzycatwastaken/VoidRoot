#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <limits> // For std::numeric_limits
#include "include/Player.hpp"
#include "include/Save.hpp"
#include "include/Location.hpp"
#include "include/TerminalUtils.hpp"

bool gameRunning = true;

// Forward declarations for functions defined later in this file
void displayStatsBox(const Player& player, const Location& currentLoc);
int getValidInput(int min, int max);

std::vector<Location> createLocations() {
    return {
        Location("Forest", "A dense forest with towering trees. The air is thick with the scent of pine."),
        Location("Cave", "A dark cave mouth leads into the mountain. Strange echoes emanate from within."),
        Location("Meadow", "A peaceful meadow filled with wildflowers. A gentle breeze carries their scent."),
        Location("Ruins", "Ancient stone ruins rise from the earth. Their purpose long forgotten."),
        Location("River", "A swift river cuts through the landscape. The water looks clean and refreshing.")
    };
}

// showGameMenu now accounts for space for the stats box
void showGameMenu(int menuX, int menuY) {
    TerminalUtils::setCursorPosition(menuX, menuY); // Position the menu
    std::cout << "=== ACTIONS ===" << std::endl;
    TerminalUtils::setCursorPosition(menuX, menuY + 1);
    std::cout << "1. Wander to new location" << std::endl;
    TerminalUtils::setCursorPosition(menuX, menuY + 2);
    std::cout << "2. Look around" << std::endl;
    TerminalUtils::setCursorPosition(menuX, menuY + 3);
    std::cout << "3. Save game" << std::endl;
    TerminalUtils::setCursorPosition(menuX, menuY + 4);
    std::cout << "4. Exit" << std::endl;
}

void startGameMenu() {
    TerminalUtils::setCursorPosition(0, 0); // Ensure cursor is at top for this menu
    std::cout << "=== VOIDROOT ===\n" << std::endl;
    std::cout << "1. Start New Game" << std::endl;
    std::cout << "2. Load Game" << std::endl;
    std::cout << "3. Exit" << std::endl;
}

void displayStatsBox(const Player& player, const Location& currentLoc) {
    int termWidth, termHeight;
    TerminalUtils::wizsize(termWidth, termHeight);
    
    // Define the dimensions of the stats box
    int boxWidth = 30;
    int boxHeight = 10;
    // Position the box on the right side
    int boxX = termWidth - boxWidth - 1; 
    int boxY = 0; // Start at the very top for alignment
    
    // Clear the area where the box will be drawn to avoid artifacts
    // This is important to "erase" any old content before redrawing
    for (int i = 0; i < boxHeight; ++i) {
        TerminalUtils::setCursorPosition(boxX, boxY + i);
        std::cout << std::string(boxWidth, ' '); // Clear the line with spaces
    }

    // Draw the box with title
    TerminalUtils::drawBox(boxX, boxY, boxWidth, boxHeight, "=== PLAYER INFO ===");
    
    // Display stats inside the box, with padding to clear old text
    TerminalUtils::setCursorPosition(boxX + 2, boxY + 2);
    std::cout << "Name   : " << player.getName() << std::string(boxWidth - 10 - player.getName().length(), ' ');
    TerminalUtils::setCursorPosition(boxX + 2, boxY + 3);
    std::cout << "Class  : " << player.getClass() << std::string(boxWidth - 10 - player.getClass().length(), ' ');
    TerminalUtils::setCursorPosition(boxX + 2, boxY + 4);
    std::cout << "Level  : " << player.getLevel() << std::string(boxWidth - 10 - std::to_string(player.getLevel()).length(), ' ');
    TerminalUtils::setCursorPosition(boxX + 2, boxY + 5);
    std::cout << "Health : " << player.getHealth() << "/100" << std::string(boxWidth - 15 - std::to_string(player.getHealth()).length(), ' ');
    TerminalUtils::setCursorPosition(boxX + 2, boxY + 6);
    std::cout << "XP     : " << player.getXP() << std::string(boxWidth - 10 - std::to_string(player.getXP()).length(), ' ');
    TerminalUtils::setCursorPosition(boxX + 2, boxY + 8);
    std::cout << "Location: " << currentLoc.getName() << std::string(boxWidth - 12 - currentLoc.getName().length(), ' ');
    std::cout.flush(); // Ensure all output is written to the terminal
}

int getValidInput(int min, int max, int promptX, int promptY) {
    int choice;
    while (true) {
        // Position the input prompt
        TerminalUtils::setCursorPosition(promptX, promptY);
        // Clear the line before printing the prompt to remove previous input/messages
        std::cout << std::string(70, ' '); 
        TerminalUtils::setCursorPosition(promptX, promptY);
        std::cout << "Enter your choice: ";

        if (std::cin >> choice) {
            if (choice >= min && choice <= max) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume the rest of the line
                return choice;
            } else {
                TerminalUtils::setCursorPosition(promptX, promptY + 1); // Position error message below prompt
                std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
                std::cin.clear(); // Clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            }
        } else {
            TerminalUtils::setCursorPosition(promptX, promptY + 1); // Position error message
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard non-integer input
        }
    }
}


void gameLoop() {
    Player player("NoName");
    const std::string saveFile = "savegame.txt";
    std::vector<Location> locations = createLocations();
    Location* currentLocPtr = &locations[0]; // Use a pointer to current location
    std::random_device rd;
    std::mt19937 gen(rd());

    int menuColumn = 0; // Starting column for the main menu
    int menuRow = 0; // Starting row for the main menu
    int messageRow = 12; // Row for game messages
    int promptRow = 10; // Row for input prompt


    while (gameRunning) {
        TerminalUtils::clearScreen();
        startGameMenu(); // This menu starts at (0,0)
        int choice = getValidInput(1, 3, 0, 5); // Prompt for main menu choices

        if (choice == 1) {
            std::string name;
            TerminalUtils::setCursorPosition(0, 5); // Position for name input
            std::cout << "Enter your name: ";
            std::getline(std::cin, name);
            player = Player(name);

            // Start in a random location
            std::uniform_int_distribution<> dis(0, locations.size() - 1);
            int startLocIndex = dis(gen);
            currentLocPtr = &locations[startLocIndex]; // Update the pointer
            
            bool exploring = true;
            while (exploring && gameRunning) {
                TerminalUtils::clearScreen(); // Clear screen at start of each exploration loop
                
                // Draw all UI elements
                showGameMenu(menuColumn, menuRow);
                displayStatsBox(player, *currentLocPtr); // Redraw stats box
                
                // Position for game messages (e.g., location description)
                TerminalUtils::setCursorPosition(menuColumn, messageRow);
                // Display current location info
                std::cout << "You are in the " << currentLocPtr->getName() << ".\n";
                currentLocPtr->lookAround(); // This will print its own header and description

                TerminalUtils::setCursorPosition(menuColumn, promptRow); // Position for input prompt
                choice = getValidInput(1, 4, menuColumn, promptRow); // Use the robust getValidInput

                // Clear the message area before displaying new action output
                for(int i = messageRow; i < promptRow; ++i) {
                    TerminalUtils::setCursorPosition(menuColumn, i);
                    std::cout << std::string(70, ' '); // Clear line
                }
                TerminalUtils::setCursorPosition(menuColumn, messageRow); // Reset cursor for new message

                if (choice == 1) {
                    TerminalUtils::setCursorPosition(menuColumn, messageRow);
                    std::cout << "Available locations:\n";
                    for (size_t i = 0; i < locations.size(); ++i) {
                        TerminalUtils::setCursorPosition(menuColumn, messageRow + 1 + i); // List locations below
                        std::cout << i + 1 << ". " << locations[i].getName() << std::endl;
                    }
                    
                    TerminalUtils::setCursorPosition(menuColumn, messageRow + 1 + locations.size() + 1); // Position for location choice prompt
                    std::cout << "Where would you like to go? ";
                    int locChoice = getValidInput(1, static_cast<int>(locations.size()), menuColumn, messageRow + 1 + locations.size() + 2); // Pass coordinates
                    
                    currentLocPtr = &locations[locChoice - 1]; // Update the pointer
                    // The loop will clear the screen and redraw everything, so no explicit clear here
                }
                else if (choice == 2) {
                    currentLocPtr->lookAround();
                }
                else if (choice == 3) {
                    if (saveGame(player, saveFile)) {
                        std::cout << "Game saved successfully.\n";
                    } else {
                        std::cout << "Failed to save game.\n";
                    }
                }
                else if (choice == 4) {
                    exploring = false;
                }
                // Pause for user to read messages before clearing and redrawing
                if (choice != 1 && choice != 4) { // Don't pause if changing location or exiting as screen clears anyway
                    TerminalUtils::setCursorPosition(menuColumn, promptRow + 2); // Position below input/error
                    std::cout << "Press Enter to continue...";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Wait for Enter
                }
            }
        }
        else if (choice == 2) {
            if (loadGame(player, saveFile)) {
                // If you implemented location saving/loading, you'd find the correct location here
                // For now, currentLocPtr remains at its default or last set value if not explicitly loaded.
                TerminalUtils::clearScreen();
                std::cout << "Game loaded successfully.\n";
                displayStatsBox(player, *currentLocPtr); // Display loaded stats
                player.displayStatus(); // This outputs to console, consider if it conflicts with UI
                TerminalUtils::setCursorPosition(0, 20); // Move cursor after status display
                std::cout << "Press enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                TerminalUtils::setCursorPosition(0, 5);
                std::cout << "No save found, please start a new game.\n";
                std::cout << "Press enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        else if (choice == 3) {
            std::cout << "Exiting the game." << std::endl;
            gameRunning = false;
        }
    }
    TerminalUtils::clearScreen(); // Clear screen before final exit
}

int main() {
    gameLoop();
    return 0;
}