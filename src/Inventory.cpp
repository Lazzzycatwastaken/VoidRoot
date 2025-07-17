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

void Inventory::saveToFile(std::ofstream& ofs) const {
    ofs << items.size() << '\n';
    for (const auto& item : items) {
        ofs << item << '\n';
    }
}

void Inventory::loadFromFile(std::ifstream& ifs) {
    items.clear();
    size_t size;
    ifs >> size;
    ifs.ignore();

    for (size_t i = 0; i < size; ++i) {
        std::string item;
        std::getline(ifs, item);
        items.push_back(item);
    }
}
