// Inventory.cpp
#include "Inventory.hpp"
#include <iostream>

void Inventory::addItem(const std::string& item) {
    items.push_back(item);
}

void Inventory::show() const {
    std::cout << "\n-- Inventory --\n";
    if (items.empty()) {
        std::cout << "Empty.\n";
        return;
    }
    for (const auto& item : items)
        std::cout << "- " << item << '\n';
}
