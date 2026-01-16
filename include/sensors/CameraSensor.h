#pragma once
#include "Sensor.h"
#include "../world/GridWorld.h"
#include "../world/WorldObject.h"
#include <vector>

class CameraSensor : public Sensor {
public:
    CameraSensor(); // Constructor
    // This function searches for objects inside camera sensor range and fills readings vector with data it receives
    void sense(const GridWorld& world, const Position& selfPosition, Direction dir) override;
    const std::vector<SensorReading>& getReadings() const { return readings; }
};