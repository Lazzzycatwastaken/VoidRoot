#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <string>
#include <vector>

class Location {
public:
    Location(const std::string& name, const std::string& description);
    
    std::string getName() const;
    std::string getDescription() const;
    void lookAround() const;
    
private:
    std::string name;
    std::string description;
};

#endif