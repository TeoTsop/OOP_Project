//Header file for the grid

#pragma once

#include <vector> //In order to use a vector to store the objects on the grid
#include <memory> //In order to use the unique_ptr
#include <string> //In order to use the variable type string
#include "../common/utils.h"
#include "../common/enums.h"
//Included in order to generate all the objects inside the grid by calling their constructors
//and destroying them afterwards
#include "../objects/MovingCar.h"
#include "../objects/MovingBike.h"
#include "../objects/StationaryVehicle.h"
#include "../objects/TrafficLight.h"
#include "../objects/TrafficSign.h"
#include "WorldObject.h" //Base class for all objects


class GridWorld {
private:
    int width;                                                  //The width of the world
    int height;                                                 //The height of the world
    int numOfMovingCars, numOfMovingBikes;                      //The number of moving cars and bikes in the grid
    int numOfTrafficLights, numOfStopSigns, numOfStoppedCars;   //The number of traffic lights, stop signs and stopped cars in the grid
    int currentTick;                                            //The current tick the world is in
    vector<unique_ptr<WorldObject>> objects;                    //The objects inside the world

public:
    //Constructor of the grid world
    GridWorld(int width, int height, int nOMC, int nOMB, int nOTL, int nOSS, int nOSC);

    //Adds objects to the grid
    void addObject(unique_ptr<WorldObject> obj);

    //When clock ticks all objects get updated
    void update();

    //Removes objects (for example if it got out of bounds)
    void removeObject(WorldObject* obj);

    //Within bounds check
    bool isInBounds(const Position& pos) const;

    //Returns all the objects in a certain position
    vector<WorldObject*> getObjectsAt(const Position& pos) const;

    //Visualisation function for the grid
    void renderer () const;

    //Getters for the height width and current tick of the world
    int getWidth() const;
    int getHeight() const;
    int getCurrentTick() const;

};