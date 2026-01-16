#include "../../include/sensors/LidarSensor.h"
#include "../../include/common/utils.h"
#include "../../include/common/enums.h"
#include "../../include/world/GridWorld.h"

LidarSensor::LidarSensor()
    : Sensor(SensorType::LIDAR, 9, 0.87, 0.99) {} // baseAccuracy is 99 for Lidar and range is 9

void LidarSensor::sense(const GridWorld& world, const Position& selfPosition, Direction dir) {
    clear(); // At the beginning of every tick we clear the vector readings from previous tick

    int half = range / 2;  // For 9x9, half = 4 (radius of search square)
    
    // Checking for objects in a 9x9 array with centre the position of sensor-Vehicle
    for (int dx = -half; dx <= half; ++dx) {
        for (int dy = -half; dy <= half; ++dy) {
            // Calculate position of searching point
            Position p = selfPosition + Position(dx, dy);
            const auto& objs = world.getObjectsAt(p);

            if (objs.empty()) continue;

            for (const WorldObject* obj : objs) {
                ObjectType type = obj->getObjectType();

                SensorReading reading(type, p, obj->getId());
                int mandist = p.ManDist(selfPosition); //Manhattan distance between sensor-Vehicle and target position

                //Confidence computation segment
                //Distance factor : from 0.1(furthest) to 1.0(closest)
                double distanceFactor;
                double maxManhattan = 8.0; // half+half = 4+4 = 8 in Manhattan Distance
                if (mandist > maxManhattan) { distanceFactor = 0.0; } //Out of sensor read reach
                else { distanceFactor = distanceAccuracy * (1.0-(mandist/maxManhattan)); }

                //Classification factor
                double classificationFactor;
                //Base category factor 1.0 (for moving objects)
                double categoryFactor = 1.0;
                //Category factor gets decreased for stationary objects
                switch (type) {
                    case ObjectType::STOPPED_CAR: categoryFactor = 0.9; break;
                    case ObjectType::TRAFFIC_LIGHT: categoryFactor = 0.8; break;
                    case ObjectType::TRAFFIC_SIGN: categoryFactor = 0.75; break;
                    default: categoryFactor = 1.0;
                }
                //Small dependency on the distance from sensor
                double distanceClassificationFactor = 0.5 + 0.5*(1.0-(mandist/maxManhattan));

                classificationFactor = classificationAccuracy * categoryFactor * distanceClassificationFactor;

                //Total accuracy of sensor
                //Weights
                //The lidar sensor is more certain about the distance more than the classification of the object detected
                //So it is natural to account the distance more in its overall confidence without ignoring the classification factor
                double distanceWeight = 0.7;
                double classificlationWeight = 0.3;

                double confidence = distanceWeight*distanceFactor + classificlationWeight*classificationFactor;

                int noise = ((rand() % 101) / 1000.0) - 0.05;  //Account for random noise (from -5% to 5%)
                confidence += noise;

                //Ensure confidence levels stay between 0 and 1
                if (confidence < 0) confidence = 0.0;
                if (confidence > 100) confidence = 1.0;

                reading.setSensorType(SensorType::LIDAR);
                reading.setDistance(mandist);
                reading.setReadingConfidence(confidence);
                readings.push_back(reading);
            }
        }
    }
}