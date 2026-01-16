#pragma once
#include "Sensor.h"
#include "../world/GridWorld.h"
#include "../world/WorldObject.h"
#include <vector>

class LidarSensor : public Sensor {
public:
    LidarSensor(); // Constructor
    // This function searches for objects inside lidar sensor range and fills readings vector with data it receives 
    void sense(const GridWorld& world, const Position& selfPosition, Direction dir) override;
    const std::vector<SensorReading>& getReadings() const { return readings; }
};