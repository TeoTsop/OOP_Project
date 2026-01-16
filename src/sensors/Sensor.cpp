#include "../../include/sensors/Sensor.h"
#include "../../include/world/GridWorld.h"

Sensor::Sensor(SensorType sensor, int r, int acc1, int acc2)
    : sensor(sensor), range(r), classificationAccuracy(acc1), distanceAccuracy(acc2) {}

void Sensor::clear () {
    readings.clear();
}

double Sensor::computeConfidence () {
    if (readings.empty()) {
        return 0.0;
    }

    double sum = 0.0;
    for (const auto& r : readings) {
        sum += r.getReadingConfidence();
    }

    confidence = (sum / readings.size())/100;
    return confidence;
}