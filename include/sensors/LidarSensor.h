#pragma once

#include <vector>
#include <string>
#include "../../include/world/WorldObject.h"
#include "../../include/common/utils.h"
#include "../../include/objects/TrafficLight.h"
#include "../../include/objects/TrafficSign.h"
#include "Sensor.h"

class LidarSensor : public Sensor {
private:
    int range;
    int baseAccuracy;
public:
    // Constructor
    LidarSensor(int range = 9, int baseAccuracy = 99);

    void sense(const GridWorld& world, const Position& selfPosition, Direction selfDirection) override;

    // Getters
    int getRange() const;
    int getBaseAccuracy() const;
    Position relativePosition(int dx, int dy, Direction dir);

    void clear();
};
