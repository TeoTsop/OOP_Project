//Implementation for the parent class of the movng cars and bikes

#include <string> //In order to be able to use the string variable type
#include "../../include/world/MovingObject.h" //The header file from where the functions below will be called
#include "../../include/world/GridWorld.h" //The header file of the simulation's world

using namespace std;

//Constrctor for a moving object
MovingObject::MovingObject (const string& id, char glyph, const Position& position,
                            const ObjectType& objectType, const SpeedState& speedState,
                            const Direction& direction, GridWorld* world)
    : WorldObject(id, glyph, position, objectType, world), speedState(speedState), direction(direction) {
//Empty
}

//Getter functions for the speed and direction of the moving vehicle
SpeedState MovingObject::getSpeedState () const { return speedState; }
Direction MovingObject::getDirection () const { return direction; }

//Destructor a moving object
MovingObject::~MovingObject () {}