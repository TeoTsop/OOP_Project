#include "../../include/world/GridWorld.h"
#include <algorithm>
#include <iostream>

using namespace std;

// Constructor
GridWorld::GridWorld(int w, int h): width(w), height(h), currentTick(0) {
    cout << "GridWorld initialized with dimensions " << width << "x" << height << endl;
}

// Add Object
void GridWorld::addObject(unique_ptr<WorldObject> obj) {
    objects.push_back(move(obj));
}

// Update World
void GridWorld::update() {
    ++currentTick;
    for (size_t i = 0; i < objects.size(); ++i)
    {
        WorldObject* obj = objects[i].get();
        // Object updates
        obj->update(*this);
        // If an object gets out of bounds it gets deleted
        if (!isInBounds(obj->getPosition())) {
            cout << "[-WORLD] Object " << obj->getId() << " moved out of bounds and will be removed." << endl;
            removeObject(obj);
            --i; // adjust index after erase
        }
    }
}

// Remove Object
void GridWorld::removeObject(WorldObject* obj) {
    auto it = find_if(objects.begin(), objects.end(),
        [obj](const unique_ptr<WorldObject>& o) {
            return o.get() == obj;
        });

    if (it != objects.end()) {
        objects.erase(it); 
    }
}

// Check Bounds
bool GridWorld::isInBounds(const Position& pos) const {
    return (pos.getX() >= 0) && (pos.getX() < width) && (pos.getY() >= 0) && (pos.getY() < height);
}

// Get Objects at a given position
vector<WorldObject*> GridWorld::getObjectsAt(const Position& pos) const {
    vector<WorldObject*> result;
    for (const auto& obj : objects) {
        if (obj->getPosition() == pos) {
            result.push_back(obj.get());
        }
    }
    return result;
}

// Getters
int GridWorld::getWidth() const { return width; }
int GridWorld::getHeight() const { return height; }
int GridWorld::getCurrentTick() const { return currentTick; }