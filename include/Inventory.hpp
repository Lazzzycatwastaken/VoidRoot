#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <vector>
#include <string>
#include <fstream>

class Inventory {
private:
    std::vector<std::string> items;

public:
    void addItem(const std::string& item);
    void show() const;

    // Add these:
    void saveToFile(std::ofstream& ofs) const;
    void loadFromFile(std::ifstream& ifs);
};

#endif
