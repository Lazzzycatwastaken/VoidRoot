#ifndef TERMINAL_UTILS_HPP
#define TERMINAL_UTILS_HPP

#include <string>
#include <iostream> // For std::cout, std::cin, std::endl

// This namespace encapsulates terminal utility functions.
namespace TerminalUtils {
    /**
     * @brief Clears the entire terminal screen.
     * Uses ANSI escape codes for broad compatibility.
     */
    void clearScreen();

    /**
     * @brief Sets the cursor position on the terminal.
     * @param x The column (0-indexed).
     * @param y The row (0-indexed).
     * Uses ANSI escape codes.
     */
    void setCursorPosition(int x, int y);

    /**
     * @brief Retrieves the width and height of the terminal window.
     * @param width Reference to an integer to store the terminal width.
     * @param height Reference to an integer to store the terminal height.
     * Uses platform-specific calls (Windows API or ioctl for Unix-like systems).
     */
    void wizsize(int& width, int& height);

    /**
     * @brief Draws a box on the terminal using Unicode box-drawing characters.
     * @param x The starting column for the top-left corner of the box (0-indexed).
     * @param y The starting row for the top-left corner of the box (0-indexed).
     * @param width The width of the box.
     * @param height The height of the box.
     * @param title An optional title to display on the top border of the box.
     */
    void drawBox(int x, int y, int width, int height, const std::string& title = "");
}

#endif // TERMINAL_UTILS_HPP