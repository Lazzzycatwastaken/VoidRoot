#include "World.hpp"
#include <cstdlib>

std::string World::getRandomLocation() {
    std::vector<std::string> locations = {
        "Shaded Forest",
        "Grassy Meadow",
        "Rocky Hillside",
        "Foggy Marsh",
        "Sunny Glade",
        "Winding Riverbank",
        "Mossy Cave Entrance",
        "Pinewood Thicket",
        "Dry Creek Bed",
        "Windy Cliffs",
        "Blooming Field",
        "Quiet Lake Shore",
        "Overgrown Trail",
        "Mountain Foot",
        "Fern-Covered Gully"
    };
    return locations[rand() % locations.size()];
}
