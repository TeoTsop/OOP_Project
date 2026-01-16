#include "../../include/sensors/CameraSensor.h"
#include "../../include/common/utils.h"
#include "../../include/common/enums.h"
#include "../../include/world/GridWorld.h"

CameraSensor::CameraSensor()
    : Sensor(SensorType::LIDAR, 7, 0.95, 0.87) {} // Base accuracy for camera sensor is 95 and range is 7

void CameraSensor::sense(const GridWorld& world, const Position& selfPosition, Direction dir) {
    clear();

    int half = range / 2; // 7x7 ->3 (radius of search square)
    // They will get values based on direction of vehicle
    int startDx = 0, endDx = 0; 
    int startDy = 0, endDy = 0;

    // Calculating the limits of the 7x7 array in front of the vehicle, depending of vehicle direction
    switch (dir) {
        case Direction::NORTH:
            startDx = -half; endDx = half;
            startDy = 1; endDy = range;
            break;

        case Direction::SOUTH:
            startDx = -half; endDx = half;
            startDy = -1; endDy = -range;
            break;

        case Direction::EAST:
            startDx = 1; endDx = range;
            startDy = -half; endDy = half;
            break;

        case Direction::WEST:
            startDx = -range; endDx = -1;
            startDy = -half; endDy = half;
            break;
    }

    // Checking for objects in a 7x7 array in front of the position of sensor-Vehicle
    for (int dx = startDx; dx <= endDx; ++dx) {
        for (int dy = startDy; dy <= endDy; ++dy) {
            Position p(selfPosition.getX() + dx, selfPosition.getY() + dy);
            const auto& objs = world.getObjectsAt(p);

            for (const WorldObject* obj : objs) {
                SensorReading reading(obj->getObjectType(), p, obj->getId());
                
                //Reading for the different object types
                if (obj->getObjectType() == ObjectType::TRAFFIC_LIGHT) {
                    const TrafficLight* light = dynamic_cast<const TrafficLight*>(obj);
                    if (light) {
                        reading.setTrafficLightColor(light->getColor());
                    }
                } else if (obj->getObjectType() == ObjectType::TRAFFIC_SIGN) {
                    const TrafficSign* sign = dynamic_cast<const TrafficSign*>(obj);
                    if (sign) {
                        reading.setSignText(sign->getSignText());
                    }
                } else if (obj->getObjectType() == ObjectType::MOVING_CAR ||
                           obj->getObjectType() == ObjectType::MOVING_BIKE) {
                    const MovingObject* movingObj = dynamic_cast<const MovingObject*>(obj); // We cast it to movingObject* so we can use functions of Moving Object
                    if (movingObj) {
                        reading.setSpeedState(movingObj->getSpeedState());
                        reading.setDirection(movingObj->getDirection());
                    }
                }

                int mandist = p.ManDist(selfPosition); //Manhattan distance between sensor-Vehicle and target position

                //Confidence computation segment
                //Distance factor : from 0.1(furthest) to 1.0(closest)
                double distanceFacator;
                double maxManhattan = 10.0; // half + range = 3 + 7 = 10
                if (mandist > maxManhattan) { distanceFacator = 0.0; } //Ignor objects outside of the grid
                else { distanceFacator = distanceAccuracy * (1.0 - (mandist/maxManhattan)); }

                //Classification factor
                double classificationFactor;
                //Base category factor 1.0 (for moving objects)
                double categoryFactor = 1.0;
                //Category factor gets decreased for moving objects
                switch (obj->getObjectType()) {
                    case ObjectType::MOVING_CAR: categoryFactor = 0.9; break;
                    case ObjectType::MOVING_BIKE: categoryFactor = 0.8; break;
                    default: categoryFactor = 1.0;
                }
                //Small dependency on the distance from sensor
                double distanceClassificationFactor = 0.6 + 0.4*(1.0-(mandist/maxManhattan));

                classificationFactor = classificationAccuracy * categoryFactor * distanceClassificationFactor;

                //Total accuracy of sensor
                //Weights
                //The camera sensor is more confident about the type of the object and its properties more than its distance from
                //the sensor itself. That's why in the overall confidence the classification factor is accounted for more than the distance one
                double distanceWeight = 0.3;
                double classificlationWeight = 0.7;

                double confidence = distanceWeight*distanceFacator + classificlationWeight*classificationFactor;

                int noise = ((rand() % 101) / 1000.0) - 0.05;  //Account for random noise (from -5% to 5%)
                confidence += noise;

                //Ensure confidence levels stay between 0 and 1
                if (confidence < 0) confidence = 0.0;
                if (confidence > 100) confidence = 1.0;

                reading.setSensorType(SensorType::CAMERA);
                reading.setDistance(mandist);
                reading.setReadingConfidence(confidence);
                reading.setDistance(mandist);
                readings.push_back(reading);
            }
        }
    }
}