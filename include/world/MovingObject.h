//Header file for the parent class of the movng cars and bikes

#include "common/enums.h" //In order to use the enums ObjectType, Direction, SpeedState
#include "common/position.h" //In order to be able to trach the position of the moving vehicle
#include "WorldObject.h" //Included since WorldObject is the parent class for all object in the grid

#include <string> //In order to be able to use the string variable type

#pragma once

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
                      const ObjectType& objectType, SpeedState speedState,
                      Direction direction);
        
        //Virtual getters for the moving object's id, glyph, position, speed, direction
        SpeedState getSpeedState ();
        Direction getDirection ();

        //Virtua

        //Virtual function to update a moving object's state (overrides WorldObject)
        virtual void update () = 0;

        //Virtual destructor for a moving object
        virtual ~MovingObject ();
};