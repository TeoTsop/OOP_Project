#include "../../include/world/GridWorld.h"
#include "include/objects/MovingCar.h"
#include "include/objects/MovingBike.h"
#include "include/objects/StationaryVehicle.h"
#include "include/objects/TrafficLight.h"
#include "include/objects/TrafficSign.h"
#include "include/common/utils.h"
#include "include/common/enums.h"
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

//Constructor for the grid world
//Call the construction of all the objects in the grid
GridWorld::GridWorld(int w, int h, int nOMC, int nOMB, int nOTL, int nOSS, int nOSC)
                    : width(w), height(h), currentTick(0), numOfMovingCars(nOMC), numOfMovingBikes(nOMB),
                      numOfTrafficLights(nOTL), numOfStopSigns(nOSS), numOfStoppedCars(nOSC) {
    
    //Constructing and placing all the moving objects first
    //Constructing the moving cars first
    for (size_t i=0; i<this->numOfMovingCars; i++) {
        //Generate random position for the moving vehicle
        Position randomCarPosition = Utils::randomPosition(width, height);
        //Generate a random direction for the moving vehicle to head towards
        Direction randomCarDirection = Utils::randomDirection();
        //Generate a random speed state (except STOPPED) for the moving vehicle to have
        SpeedState randomCarSpeed = Utils::randomSpeed();
        GridWorld::addObject(std::make_unique<MovingCar>("MCAR"+to_string(i),
                                                         randomCarPosition,
                                                         randomCarSpeed,
                                                         randomCarDirection));
    }

    //Constructing the moving bikes likewise
    for (size_t i=0; i<this->numOfMovingBikes; i++) {
        //Generate random position for the moving vehicle
        Position randomBikePosition = Utils::randomPosition(width, height);
        //Generate a random direction for the moving vehicle to head towards
        Direction randomBikeDirection = Utils::randomDirection();
        //Generate a random speed state (except STOPPED) for the moving vehicle to have
        SpeedState randomBikeSpeed = Utils::randomSpeed();
        GridWorld::addObject(std::make_unique<MovingCar>("MBIKE"+to_string(i),
                                                         randomBikePosition,
                                                         randomBikeSpeed,
                                                         randomBikeDirection));
    }

    //Constructing and placing all the stationary objects next
    //Constructing the stationary cars first
    for (size_t i=0; i<this->numOfStoppedCars; i++) {
        //Generate random position for the stationary vehicle
        Position randomCarPosition = Utils::randomPosition(width, height);
        GridWorld::addObject(std::make_unique<MovingCar>("SCAR"+to_string(i),
                                                         randomCarPosition));
    }

    //Constructing the stop signs likewise
    for (size_t i=0; i<this->numOfStopSigns; i++) {
        //Generate random position for the stop sign
        Position randomStopSignPosition = Utils::randomPosition(width, height);
        GridWorld::addObject(std::make_unique<MovingCar>("STSI"+to_string(i),
                                                         randomStopSignPosition));
    }

    //Constructing the traffic lights
    for (size_t i=0; i<this->numOfTrafficLights; i++) {
        TrafficLightColor randomTrafficLightColor = Utils::randomTrafficLightColor();
        //Generate random position for the traffic light vehicle
        Position randomTrafficLightPosition = Utils::randomPosition(width, height);
        GridWorld::addObject(std::make_unique<MovingCar>("STSI"+to_string(i),
                                                         randomTrafficLightPosition));
    }

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
        obj->update();
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