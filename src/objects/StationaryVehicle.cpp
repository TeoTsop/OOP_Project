//Implementation for the functions inside the stationary vehicle class

#include <iostream>
#include "../../include/objects/StationaryVehicle.h" //The header file from where the functions below will be called

using namespace std;

//Constructor for the stationary vehicle
StationaryVehicle::StationaryVehicle (const std::string& id, const Position& position, GridWorld* world)
    : StaticObject(id, 'P', position, ObjectType::STOPPED_CAR, world) {
    
    cout << "[+PARKED: " << id << "] Parked at ("
         << position.getX() << ", " << position.getY() << ")" 
         << endl;
}

//Function for world update (does nothing)
void StationaryVehicle::update () { return; }

//Destructor for the stationary vehicle
StationaryVehicle::~StationaryVehicle () {

    cout << "[-PARKED: " << id << "]" << endl;

}