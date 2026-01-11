#pragma once

#include "../world/StaticObject.h"

class StationaryVehicle : public StaticObject {
public:
    StationaryVehicle(const std::string& id, const Position& position);
};

