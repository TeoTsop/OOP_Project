//Header file for moving objects
//Parent class of the movng cars and bikes

#pragma once

#include <string> //In order to be able to use the string variable type
#include "../common/enums.h" //In order to use the enums ObjectType, Direction, SpeedState
#include "../common/position.h" //In order to be able to track the position of the moving vehicle
#include "WorldObject.h" //Included since WorldObject is the parent class for all object in the grid

//Forward declaration
class GridWorld;

//Parent class for all moving objects
//Child class of WorldObject class
class MovingObject : public WorldObject {
    protected:
        SpeedState speedState;
        Direction direction;
    public:
        //Constructor for a moving object
        MovingObject (const std::string& id, char glyph, const Position& position,
                      const ObjectType& objectType, const SpeedState& speedState,
                      const Direction& direction, GridWorld* World);
        
        //Getters for the moving object's speed and direction
        SpeedState getSpeedState () const;
        Direction getDirection () const;

        //Virtual function to update a moving object's state
        virtual void update () = 0;

        //Virtual destructor for a moving object
        virtual ~MovingObject ();
};