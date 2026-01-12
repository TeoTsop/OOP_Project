//Implementation for the functions inside the stationary vehicle class

#include <iostream>
#include "../../include/objects/StationaryVehicle.h" //The header file from where the functions below will be called

using namespace std;

//Constructor for the stationary vehicle
StationaryVehicle::StationaryVehicle (const std::string& id, const Position& position)
    : StaticObject(id, 'P', position, ObjectType::STOPPED_CAR) {
    
    cout << "[+PARKED: " << id << "] Parked at ("
         << position.getX() << ", " << position.getY() << ")" 
         << endl;
}

//Destructor for the stationary vehicle
StationaryVehicle::~StationaryVehicle () {

    cout << "[-PARKED: " << id << "]" << endl;

}