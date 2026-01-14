//Implementation for the functions inside the moving car class

#include <iostream>
#include <string> //In order to be able to use the string variable type
#include "../../include/objects/MovingCar.h" //The header file from where the functions below will be called
#include "../../include/world/GridWorld.h" //The header file of the simulation's world

using namespace std;

//Constrctor for a moving car
MovingCar::MovingCar (const string& id, const Position& position,
                      SpeedState speedState, Direction direction,
                      GridWorld* world)
    : MovingObject(id, 'C', position, ObjectType::MOVING_CAR, speedState, direction, world) {

    cout << "[+MOVING: " << id << "] Starting at ("
         << position.getX() << ", " << position.getY() << ") with "
         << (speedState == FULL_SPEED ? "FULL SPEED" : "HALF_SPEED") 
         << " and towards the " << (direction == NORTH ? "NORTH" :
                                    direction == WEST ? "WEST" :
                                    direction == EAST ? "EAST" :
                                    "SOUTH") << endl;

}

//Update the state of the object
void MovingCar::update () {

    //Move the object according to the speed and direction it is heading towards
    if (this->getSpeedState() == SpeedState::FULL_SPEED) { //Case where the vehicle is moving at full speed
        switch (this->getDirection()) {
            case Direction::NORTH: this->position.setY(this->position.getY() + 2); break;
            case Direction::SOUTH: this->position.setY(this->position.getY() - 2); break;
            case Direction::EAST: this->position.setX(this->position.getX() + 2); break;
            default: this->position.setX(this->position.getX() - 2); break;
        }
    }
    else { //Case where the vehicle is moving at normal speed
        switch (this->getDirection()) {
            case Direction::NORTH: this->position.setY(this->position.getY() + 1); break;
            case Direction::SOUTH: this->position.setY(this->position.getY() - 1); break;
            case Direction::EAST: this->position.setX(this->position.getX() + 1); break;
            default: this->position.setX(this->position.getX() - 1); break;
        }
    }
    //In case the moving vehicle gets out of bounds then remove it from the grid
    if (!this->world->isInBounds(this->getPosition())) { this->world->removeObject(this); return; }

    //Chance for the car to change its speed (3/10) and direction (5/10) just to spice things up a bit
    //The vehicle is not an intelligent one it is just affected by fate!
    int randValueForSpeed = Utils::randomInteger(1,10);
    if (randValueForSpeed > 7) { //If there is a successful number pull then choose the other speed than the current one
        if (this->speedState == SpeedState::FULL_SPEED) {this->speedState = SpeedState::HALF_SPEED;}
        else {this->speedState = SpeedState::FULL_SPEED;}
    }
    int randValueForDirection = Utils::randomInteger(1,10);
    if (randValueForDirection > 5) {
        while (1) { //If there is a successful number pull then iterate getting random directions till one is
                    //found different than the current one
            Direction randomNewDirection = Utils::randomDirection();
            if (randomNewDirection == this->direction) {continue;}
            else {this->direction = randomNewDirection; break;}
        }
    }
}

//Destructor for the moving car
MovingCar::~MovingCar () {

    cout << "[-MOVING: " << id << "]" << endl;

}