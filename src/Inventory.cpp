    #include "Inventory.hpp"
    #include <iostream>
    #include <map>

    std::map<std::string, int> items;

    void Inventory::addItem(const std::string& item) {
        if (items.find(item) != items.end()) {
            items[item]++;
        } else {
            items[item] = 1;
        }
    }

    void Inventory::show() const {
        std::cout << "\n-- Inventory --\n";
        if (items.empty()) {
            std::cout << "Empty.\n";
            return;
        }
        for (const auto& pair : items) {
            std::cout << "- " << pair.first;
            if (pair.second > 1) {
                std::cout << " x" << pair.second;
            }
            std::cout << '\n';
        }
    }

    void Inventory::saveToFile(std::ofstream& ofs) const {
        ofs << items.size() << '\n';
        for (const auto& pair : items) {
           ofs << pair.first << '\n' << pair.second << '\n';
        }
    }

    void Inventory::loadFromFile(std::ifstream& ifs) {
        items.clear();
        size_t size;
        ifs >> size;
        ifs.ignore();

        for (size_t i = 0; i < size; ++i) {
            std::string item;
            int count;
            std::getline(ifs, item);
            ifs >> count;
            ifs.ignore();
            items[item] = count;
        }
    }
