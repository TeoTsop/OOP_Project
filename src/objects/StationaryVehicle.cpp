#include "../../include/objects/StationaryVehicle.h"
#include <iostream>

StationaryVehicle::StationaryVehicle(const std::string& id, const Position& position)
    : StaticObject(id, position, 'P')   // 'P' (Parked car)
{
    std::cout << "[+PARKED: " << id << "] Parked at ("
              << position.getX() << ", " << position.getY() << ")\n";
}

char StationaryVehicle::getGlyph() const {
    return glyph;  
}
