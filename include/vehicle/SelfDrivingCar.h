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
#include "../world/MovingObject.h"

class SelfDrivingVehicle : public MovingObject {
    private:
        int minConfidenceThreshold;
        std::vector<Position*> targetPositions;

        //Sensors of the self driving vehicle
        /*
        LidarSensor lSenor;
        CameraSensor cSensor;
        RadarSensor rSensor;
        */

    public:
        //Constructor for the self driving car
        SelfDrivingVehicle (const std::string& id, const Position& position,
                            GridWorld* world, int minConfidenceThreshold,
                            const std::vector<Position*>& targetPositions);

        //Updating the state of the self driving car
        //Overriding from the Moving Objects parent class
        void update() override;

        //Destructor for the self driving vehicle
        ~SelfDrivingVehicle ();
};