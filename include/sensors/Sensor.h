#pragma once

#include "../world/GridWorld.h"
#include "../common/enums.h"

class Sensor {

protected:
    std::vector<const WorldObject*> detectedObjects;
    std::vector<Position> detectedPositions;
public:
    Sensor() =default;
    virtual ~Sensor() {};

    // Sense function is pure virtual (Every sensor implements it differently)
    virtual void sense(
        const GridWorld& world,
        const Position& selfPosition,
        Direction selfDirection
    ) = 0;
    
    const std::vector<const WorldObject*>& getDetectedObjects() const;
    const std::vector<Position>& getDetectedPositions() const;
};
