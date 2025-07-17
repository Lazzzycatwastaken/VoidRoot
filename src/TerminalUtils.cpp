#include <iostream>
#include <string>
#include <../include/TerminalUtils.hpp> // Adjusted include path if necessary

// Platform-specific headers for terminal manipulation
#ifdef _WIN32
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#endif

namespace TerminalUtils {

void clearScreen() {
    std::cout << "\033[2J"; // ANSI escape code for clearing the screen
    std::cout << "\033[H";  // Move cursor to top-left corner
    std::cout.flush();
}

void setCursorPosition(int x, int y) {
    // ANSI escape code for setting cursor position: \033[<ROW>;<COL>H
    // Terminal rows/columns are 1-indexed, so add 1 to x and y.
    std::cout << "\033[" << y + 1 << ";" << x + 1 << "H";
    std::cout.flush();
}

void wizsize(int& width, int& height) {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#else
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0) {
        width = ws.ws_col;
        height = ws.ws_row;
    } else {
        // Fallback if ioctl fails, common default sizes
        width = 80;
        height = 24;
    }
#endif
}

void drawBox(int x, int y, int width, int height, const std::string& title) {
    // Using ASCII characters for broader compatibility
    setCursorPosition(x, y);
    std::cout << "+" << std::string(width - 2, '-') << "+"; // Top border
    for (int i = 1; i < height - 1; ++i) {
        setCursorPosition(x, y + i);
        std::cout << "|" << std::string(width - 2, ' ') << "|"; // Side borders and interior space
    }
    setCursorPosition(x, y + height - 1);
    std::cout << "+" << std::string(width - 2, '-') << "+"; // Bottom border

    if (!title.empty()) {
        // Calculate position to center the title on the top border
        int titleStart = x + 1 + (width - 2 - title.length()) / 2;
        if (titleStart < x + 1) titleStart = x + 1; // Ensure title doesn't go out of bounds
        
        setCursorPosition(titleStart, y);
        // Print title, overwriting part of the top border
        std::cout << title;
    }
    std::cout.flush(); // Ensure all output is written
}

} // namespace TerminalUtils