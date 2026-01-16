#pragma once

#include <vector>
#include "../../include/sensors/SensorReading.h"

class SensorFusionEngine {
public:
    // This function gives a shorter and merged version of the vector with all sensor readings for a specific tick
    std::vector<SensorReading> fuseSensorData(const vector<SensorReading>& allReadings, double minConfidenceThreshold) const;
};