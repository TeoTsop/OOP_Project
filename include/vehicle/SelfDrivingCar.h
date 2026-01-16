//Header file for the self driving car

#pragma once

#include <vector>
#include <string>
#include "../common/enums.h"    //Used for the objectType, speedState and Direction enums
#include "../common/position.h" //Used for the position variable
#include "../common/utils.h"    //Used for the seed based random number generators
//Including the sensor header files
#include "../sensors/LidarSensor.h"
#include "../sensors/CameraSensor.h"
#include "../sensors/RadarSensor.h"
#include "../sensors/Sensor.h"
#include "SensorFusionEngine.h"
#include "../world/MovingObject.h" //Included since it is the parent class of the autonomous vehicle class

class SelfDrivingVehicle : public MovingObject {
    private:
        int minConfidenceThreshold; //Min confidence threshold
        std::vector<Position*> targetPositions; //Traget positions for the vehicle
        std::vector<SensorReading> sensorsData; //Data of the sensors of the vehicle

    public:
        //Constructor for the self driving car
        SelfDrivingVehicle (const std::string& id, const Position& position,
                            GridWorld* world, int minConfidenceThreshold,
                            const std::vector<Position*>& targetPositions);

        //Updating the state of the self driving car
        //Overriding from the Moving Objects parent class
        void update() override;

        std::vector<SensorReading> getSensorData ();
        void setSensorData (std::vector<SensorReading> sR);

        //Destructor for the self driving vehicle
        ~SelfDrivingVehicle ();
};