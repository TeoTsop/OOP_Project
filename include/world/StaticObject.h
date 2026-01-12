//Header file for the static objects
//Parent for STOP signs, lights, parked vehicles

#pragma once

#include <string> //In order to be able to use the string variable type
#include "../common/position.h" //In order to be able to track the position of the static object
#include "WorldObject.h" //Included since WorldObject is the parent class for all object in the grid


class StaticObject : public WorldObject {
public:
    //Constructor for a static object
    StaticObject(const std::string& id, char glyph, const Position& pos, const ObjectType& ObjectType);

    //Virtual function to update a static object's state (only for the traffic lights)
    virtual void update () = 0;

    //Virtual destructor for a static object
    virtual ~StaticObject();
};