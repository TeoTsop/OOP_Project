//Executable file for the functions inside the moving car header file

#include <iostream>
#include <string> //In order to be able to use the string variable type
#include "include/objects/MovingCar.h" //The header file from where the functions below will be called
#include "include/common/enums.h" //In order to use the enums ObjectType, Direction, SpeedState
#include "include/common/utils.h" //In order to use the randomisers

using namespace std;

//Forward Declaration
class GridWorld;

//Constrctor for a moving car
MovingCar::MovingCar (const string& id, const Position& position,
                      SpeedState speedState, Direction direction)
    : MovingObject(id, 'C', position, ObjectType::MOVING_CAR, speedState, direction) {

}

void MovingObject::update (GridWorld& world) {}

MovingCar::~MovingCar () {}
