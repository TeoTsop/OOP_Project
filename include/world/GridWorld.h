//Dimensions, objects, bounds

#pragma once

#include <vector>
#include <memory>
#include <string>
#include "WorldObject.h"  // Base class for all objects
#include "../common/position.h"

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

    // Adds objects 
    void addObject(unique_ptr<WorldObject> obj);

    // When clock ticks all objects get updated
    void update();

    // Removes objects (for example if it got out of bounds)
    void removeObject(WorldObject* obj);

    // Within bounds check
    bool isInBounds(const Position& pos) const;

    // Επιστρέφει όλα τα αντικείμενα σε μία θέση
    vector<WorldObject*> getObjectsAt(const Position& pos) const;

    // Getters
    int getWidth() const;
    int getHeight() const;
    int getCurrentTick() const;
};