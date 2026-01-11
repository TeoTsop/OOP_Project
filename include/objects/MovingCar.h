//Header file for the moving cars

#include "common/enums.h" //In order to use the enums ObjectType, Direction, SpeedState
#include "common/position.h" //In order to be able to trach the position of the moving vehicle
#include "common/utils.h" //In order to use the randomisers for the starting speed direction and 
#include "world/MovingObject.h" //Included since the Moving Object class is the parent class of the moving cars

#pragma once

//The class for the moving car
class MovingCar : public MovingObject {
    public:
        //Constructor for the moving car
        MovingCar (const std::string& id, const Position& position,
                   SpeedState speedState, Direction direction);

        //Function to update the position, direction and speed of the car
        void update () override;

        //Destructor for the moving car
        ~MovingCar ();

};