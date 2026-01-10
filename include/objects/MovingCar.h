//Header file for the moving cars

#include "common/enums.h" //In order to use the enums ObjectType, Direction, SpeedState
#include "common/position.h" //In order to be able to trach the position of the moving vehicle
#include "world/MovingObject.h" //Included since the Moving Object class is the parent class of the moving cars

#pragma once

class MovingCar : public MovingObject {
    protected:
        int numberOfMovingCars = 0; //Counter to track number of moving cars existent in the grid
    public:
        //Constructor for the moving car
        MovingCar (const std::string& id, char glyph, Position position,
                   ObjectType objectType, SpeedState speedState,
                   Direction direction);

        void update (GridWorld& world) override;

        //Destructor for the moving car
        ~MovingCar ();

};