//Executable file for the parent class of the movng cars and bikes

#include <iostream>
#include <string> //In order to be able to use the string variable type
#include "include/world/MovingObject.h" //The header file from where the functions below will be called
#include "include/common/enums.h" //In order to use the enums ObjectType, Direction, SpeedState

using namespace std;

//Forward declaration
class GridWorld;

//Constrctor for a moving object
MovingObject::MovingObject (const string& id, char glyph, Position position,
                            ObjectType objectType, SpeedState speedState,
                            Direction direction)
    : WorldObject(id, glyph, position, objectType), speedState(speedState), direction(direction) {

//Empty for now

}

//Getter functions for the speed and direction of the moving vehicle
SpeedState MovingObject::getSpeedState () { return speedState; }
Direction MovingObject::getDirection () { return direction; }

void MovingObject::handleCrash () {



}

void MovingObject::update (GridWorld& world) {


}

//Destructor a the moving object
MovingObject::~MovingObject () {

//Empty for now
}