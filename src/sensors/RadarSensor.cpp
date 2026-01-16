#include "../../include/sensors/RadarSensor.h"
#include "../../include/common/utils.h"
#include "../../include/common/enums.h"
#include "../../include/world/GridWorld.h"

RadarSensor::RadarSensor()
    : Sensor(SensorType::LIDAR, 12, 0.95, 0.95) {} //For Radar accuracy is 99 and range is 12

void RadarSensor::sense(const GridWorld& world, const Position& selfPosition, Direction dir) {
    clear();

    for (int d = 1; d <= range; ++d) {
        Position p = selfPosition.moveInDirection(dir, d); // Goes to search position
        const auto& objs = world.getObjectsAt(p);

        for (const WorldObject* obj : objs) {
            if (obj->getObjectType() == ObjectType::TRAFFIC_LIGHT ||
                obj->getObjectType() == ObjectType::TRAFFIC_SIGN ||
                obj->getObjectType() == ObjectType::STOPPED_CAR) continue; // Radar only detects moving objects

            SensorReading reading(obj->getObjectType(), p, obj->getId());
            //Radar sensor only recognizes speed and direction
            const MovingObject* movingObj = dynamic_cast<const MovingObject*>(obj); // We cast it to movingObject* so we can use functions of Moving Object
            if (movingObj) {
                reading.setSpeedState(movingObj->getSpeedState());
                reading.setDirection(movingObj->getDirection());
            }
            int mandist = p.ManDist(selfPosition); //Manhattan distance between sensor-Vehicle and target position

            //Confidence computation segment
            //Distance factor : from 0.1(furthest) to 1.0(closest)
            double distanceFactor;
            double maxManhattan = 12.0; // Since the render distance is 12 grid spots in front of the car/sensor
            if (mandist > maxManhattan) { distanceFactor = 0.0; } //Out of sensor read reach
            else { distanceFactor = distanceAccuracy * (1.0-(mandist/maxManhattan)); }

            //Classification factor
            double classificationFactor;
            //Base category factor 1.0 (for moving objects)
            double categoryFactor = 1.0;
            //Category factor gets decreased for moving bikes
            switch (obj->getObjectType()) {
                case ObjectType::MOVING_BIKE: categoryFactor = 0.9; break;
                default: categoryFactor = 1.0;
            }
            //Small dependency on the distance from sensor
            double distanceClassificationFactor = 0.7 + 0.3*(1.0-(mandist/maxManhattan));

            classificationFactor = classificationAccuracy * categoryFactor * distanceClassificationFactor;

            //Total accuracy of sensor
            //Weights
            //The radar sensor is a bit better in the distance category and struggles more in the classification one.
            //The weight is also acccounting the fact that it cannot detect stationary objects
            double distanceWeight = 0.6;
            double classificlationWeight = 0.4;

            double confidence = distanceWeight*distanceFactor + classificlationWeight*classificationFactor;

            int noise = ((rand() % 101) / 1000.0) - 0.05;  //Account for random noise (from -5% to 5%)
            confidence += noise;

            //Ensure confidence levels stay between 0 and 1
            if (confidence < 0) confidence = 0.0;
            if (confidence > 100) confidence = 1.0;

            reading.setSensorType(SensorType::RADAR);
            reading.setDistance(mandist);
            reading.setReadingConfidence(confidence);
            readings.push_back(reading);
        }
    }
}