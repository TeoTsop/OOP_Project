#include "../../include/sensors/LidarSensor.h"
#include <iostream>
using namespace std;


LidarSensor::LidarSensor(int lidarRange, int lidarBaseAccuracy):
    range(lidarRange), baseAccuracy(lidarBaseAccuracy) {
        cout << "Lidar sensor created" << endl;
    }  

void LidarSensor::clear() {
    detectedObjects.clear();
    detectedPositions.clear();
}

// Helper function that calculates the position of the object detected on the 9x9 grid relative to the vehicle's direction
Position LidarSensor::relativePosition(int dx, int dy, Direction dir) {
    switch(dir) {
        case Direction::NORTH:    return Position(dx, dy);
        case Direction::SOUTH:    return Position(-dx, -dy);
        case Direction::WEST:     return Position(-dy, dx);
        case Direction::EAST:     return Position(dy, -dx);
    }
    return Position(dx, dy); // default fallback
}

void LidarSensor::sense(const GridWorld& world, const Position& selfPosition, Direction dir) {
    clear(); // Clears detected objects from previous cycle

    int cx = selfPosition.getX();
    int cy = selfPosition.getY();

    int half = range / 2;   // The radius of the 9x9 square which should be equal to 4

    for (int dx = -half; dx <= half; ++dx) {
        for (int dy = -half; dy <= half; ++dy) {

            Position p(cx + dx, cy + dy);
            const auto& objects = world.getObjectsAt(p);
            if (objects.empty())
                continue;
                

            for (const WorldObject* obj : objects) {
                if (dynamic_cast<const TrafficLight*>(obj) != nullptr ||
                    dynamic_cast<const TrafficSign*>(obj) != nullptr) {
                    continue;
                }

                int accuracy = baseAccuracy + Utils::randomInteger(-5, 5);

                if (accuracy < 1) {
                    continue;
                } 
                else {
                   detectedObjects.push_back(obj);
                   detectedPositions.push_back(relativePosition(dx, dy, dir));
                }


                
            }
        }
    }
}


int LidarSensor:: getRange() const {
    return range;
}

int LidarSensor:: getBaseAccuracy() const {
    return baseAccuracy;
}



