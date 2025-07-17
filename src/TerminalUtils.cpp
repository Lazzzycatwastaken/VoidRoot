#include <iostream>
#include <../include/TerminalUtils.hpp>

void TerminalUtils::drawBox(int x, int y, int width, int height, const std::string& title) {
    setCursorPosition(x, y);
    std::cout << "╔" << std::string(width - 2, '═') << "╗";
    for (int i = 1; i < height - 1; ++i) {
        setCursorPosition(x, y + i);
        std::cout << "║" << std::string(width - 2, ' ') << "║";
    }
    setCursorPosition(x, y + height - 1);
    std::cout << "╚" << std::string(width - 2, '═') << "╝";

    if (!title.empty()) {
        setCursorPosition(x + 1, y);
        std::cout << title;
    }
}