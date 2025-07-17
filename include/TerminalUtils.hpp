#include <string>
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

class TerminalUtils {
public:
    static void clearScreen() {
        // ANSI escape code to clear the screen
        std::cout << "\033[2J\033[1;1H";
    }
    static void setCursorPosition(int x, int y) {
        // ANSI escape code to set cursor position
        std::cout << "\033[" << y << ";" << x << "H";
    }
    static void hideCursor() {
        // ANSI escape code to hide the cursor
        std::cout << "\033[?25l";
    }
    static void showCursor() {
        // ANSI escape code to show the cursor
        std::cout << "\033[?25h";
    }
    static void setTextColor(int color) {
        // ANSI escape code to set text color
        std::cout << "\033[38;5;" << color << "m";
    }
    static void resetTextColor() {
        // ANSI escape code to reset text color
        std::cout << "\033[0m";
    }
    static void setBackgroundColor(int color) {
        // ANSI escape code to set background color
        std::cout << "\033[48;5;" << color << "m";
    }
    static void resetBackgroundColor() {
        // ANSI escape code to reset background color
        std::cout << "\033[0m";
    }
    static void wizsize(int& width, int& height) {
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        width = w.ws_col;
        height = w.ws_row;
    }
    static void drawBox(int x, int y, int width, int height, const std::string& title = "");
};