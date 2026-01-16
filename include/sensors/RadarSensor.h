#pragma once
#include "Sensor.h"
#include "../world/GridWorld.h"
#include "../world/WorldObject.h"
#include <vector>

class RadarSensor : public Sensor {
public:
    RadarSensor(); // Constructor
    void sense(const GridWorld& world, const Position& selfPosition, Direction dir) override;
    double computeMeasurementAccuracy(std::vector<SensorReading> readings);

    const std::vector<SensorReading>& getReadings() const { return readings; }
};