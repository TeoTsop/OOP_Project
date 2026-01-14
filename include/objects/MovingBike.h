//Header file for the moving bikes

#pragma once

#include "../common/enums.h" //In order to use the enums ObjectType, Direction, SpeedState
#include "../common/utils.h" //In order to use the randomizers for the change of speed and direction part
#include "../common/position.h" //In order to be able to track the position of the moving vehicle
#include "../world/MovingObject.h" //Included since the Moving Object class is the parent class of the moving vehicles

//The class for the moving bike
class MovingBike : public MovingObject {
    private:
        RandomGenerators& rng;  //Reference for rng
    public:
        //Constructor for the moving bike
        MovingBike (const std::string& id, const Position& position,
                    SpeedState speedState, Direction direction,
                    GridWorld* world, RandomGenerators& rng);

        //Function to update the position, direction and speed of the bike
        //Overrides the function in the base class Moving Object
        void update () override;

        //Destructor for the moving bike
        ~MovingBike ();
};