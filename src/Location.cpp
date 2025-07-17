#include "../include/Location.hpp"
#include <iostream>

Location::Location(const std::string& name, const std::string& description)
    : name(name), description(description) {}

std::string Location::getName() const {
    return name;
}

std::string Location::getDescription() const {
    return description;
}

void Location::lookAround() const {
    std::cout << "\n=== " << name << " ===\n";
    std::cout << description << "\n";
    std::cout << "================\n";
}