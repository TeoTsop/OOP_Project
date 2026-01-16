//Sensor parent class header file

#pragma once
#include <vector>
#include "../../include/common/position.h"
#include "../../include/common/enums.h"
#include "SensorReading.h"

//Forward declaration
class GridWorld;

class Sensor {
protected:
    SensorType sensor; // Type of the sensor being used
    int range; // Range of a sensor (Lidar:9, Radar:12, Camera:7)
    double classificationAccuracy; //For the object classification
    double distanceAccuracy; //For the distance from the moving vehicle
    std::vector<SensorReading> readings; // A sensor stores a vector with readings, each reading contains info about the measurement
    double confidence; // Value: (0.0-1.0). 
    //Once sense and compute accuracy functions are called this field will be given its value 
    //which is the average accuracy of all sensor reading accuracies stored in vector readings  

public:
    Sensor(SensorType sensor, int r, int classificationAccuracy, int distanceAccuracy);
    virtual ~Sensor() = default;
    
    // This function clears measurements vector for a sensor
    void clear(); 
    // This function searches for objects inside radar sensor range and fills readings vector with data it receives (every sensor implements it its own way)
    virtual void sense(const GridWorld& world, const Position& selfPosition, Direction dir) = 0;
    double computeConfidence(); 
    const std::vector<SensorReading>& getReadings() const { return readings; } // Getter for readings vector
};