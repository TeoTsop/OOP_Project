//Header file for the stationary vehicles

#pragma once

#include "../world/StaticObject.h" //Included since the Static Object class is the parent class of the stationary vehicles

//The class for the stationary vehicles
class StationaryVehicle : public StaticObject {
    public:
        //Constructor for the stationary vehicle
        StationaryVehicle(const std::string& id, const Position& position);

        //Destructor for the stationary vehicle
        ~StationaryVehicle ();
};

