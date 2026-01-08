//Dimensions, objects, bounds

#pragma once

#include <vector>
#include <memory>
#include <string>
#include "WorldObject.h"  // Base class for all objects
#include "../common/position.h"

class GridWorld {
private:
    int width;
    int height;
    int currentTick;

    // Τα αντικείμενα του κόσμου
    vector<unique_ptr<WorldObject> > objects;

public:
    // Constructor
    GridWorld(int w = 40, int h = 40);

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