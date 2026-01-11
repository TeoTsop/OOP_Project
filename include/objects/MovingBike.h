//Header file for the moving bikes

#include "common/enums.h" //In order to use the enums ObjectType, Direction, SpeedState
#include "common/utils.h" //In order to use the randomisers for the starting speed direction and 
#include "common/position.h" //In order to be able to trach the position of the moving vehicle
#include "world/MovingObject.h" //Included since the Moving Object class is the parent class of the moving cars

#pragma once

//The class for the moving bike
class MovingBike : public MovingObject {
    public:
        //Constructor for the moving bike
        MovingBike (const std::string& id, const Position& position,
                SpeedState speedState, Direction direction);

        //Function to update the position, direction and speed of the bike
        void update () override;

        //Destructor for the moving bike
        ~MovingBike ();

};