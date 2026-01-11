//Header file for the moving cars

#include "common/enums.h" //In order to use the enums ObjectType, Direction, SpeedState
#include "common/position.h" //In order to be able to trach the position of the moving vehicle
#include "common/utils.h" //In order to use the randomisers for the starting speed direction and 
#include "world/MovingObject.h" //Included since the Moving Object class is the parent class of the moving cars

#pragma once

class MovingCar : public MovingObject {
    public:
        MovingCar (const std::string& id, const Position& position,
                   SpeedState speedState, Direction direction);

        void update (GridWorld& world) override;

        //Destructor for the moving car
        ~MovingCar ();

};