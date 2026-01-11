//Executable file for the functions inside the moving car header file

#include <iostream>
#include <string> //In order to be able to use the string variable type
#include "include/world/GridWorld.h" //In order to create an instance of the world and delete the vehicle if it gets out of bounds
#include "include/objects/MovingCar.h" //The header file from where the functions below will be called
#include "include/common/enums.h" //In order to use the enums ObjectType, Direction, SpeedState
#include "include/common/utils.h" //In order to use the randomizers for the change of speed and direction part
#include "include/common/position.h" //In order to be able to update the position of the moving vehicle

using namespace std;

//Instance of the GridWorld
GridWorld world;

//Constrctor for a moving car
MovingCar::MovingCar (const string& id, const Position& position,
                      SpeedState speedState, Direction direction)
    : MovingObject(id, 'C', position, ObjectType::MOVING_CAR, speedState, direction) {

}

void MovingCar::update () {

    //Move the object according to the speed and direction it is heading towards
    if (this->getSpeedState() == SpeedState::FULL_SPEED) {
        switch (this->getDirection()) {
            case Direction::NORTH: this->position.setY(this->position.getY() + 2); break;
            case Direction::SOUTH: this->position.setY(this->position.getY() - 2); break;
            case Direction::EAST: this->position.setX(this->position.getX() + 2); break;
            default: this->position.setX(this->position.getX() - 2); break;
        }
    }
    else {
        switch (this->getDirection()) {
            case Direction::NORTH: this->position.setY(this->position.getY() + 1); break;
            case Direction::SOUTH: this->position.setY(this->position.getY() - 1); break;
            case Direction::EAST: this->position.setX(this->position.getX() + 1); break;
            default: this->position.setX(this->position.getX() - 1); break;
        }
    }
    //In case the moving vehicle gets out of bounds then remove it from the grid
    if (!world.isInBounds(this->getPosition())) { world.removeObject(this); return; }

    //Chance for the car to change its speed (3/10) and direction (5/10) just to spice things up a bit
    //The vehicle is not an intelligent one it is just affected by fate!
    int randValueForSpeed = Utils::randomInteger(1,10);
    if (randValueForSpeed > 7) { 
        if (this->speedState == SpeedState::FULL_SPEED) {this->speedState = SpeedState::HALF_SPEED;}
        else {this->speedState = SpeedState::FULL_SPEED;}
    }
    int randValueForDirection = Utils::randomInteger(1,10);
    if (randValueForSpeed > 5) { 
        while (1) {
            Direction randomNewDirection = Utils::randomDirection();
            if (randomNewDirection == this->direction) {continue;}
            else {this->direction = randomNewDirection; break;}
        }
    }
}

MovingCar::~MovingCar () {}