//Implementation of the functions inside the GridWorld class

#include <algorithm>
#include <string> //In order to use the variable type string
#include <iostream>
#include "../../include/world/GridWorld.h" //The header file from where the functions below will be called

using namespace std;

//Constructor for the grid world
//Call the construction of all the objects in the grid
GridWorld::GridWorld(unsigned int seed, int w, int h, int numTics, int nOMC, int nOMB, int nOTL,
                     int nOSS, int nOSC, int mCT, vector<Position*> targetPositions, const string& povSetting, int radius)
                    : seed(seed), width(w), height(h), currentTick(0), numberOfTics(numTics),
                      numOfMovingCars(nOMC), numOfMovingBikes(nOMB), numOfTrafficLights(nOTL),
                      numOfStopSigns(nOSS), numOfStoppedCars(nOSC), minConfidenceThreshold(mCT),
                      targetPositions(targetPositions), povSetting(povSetting), radius(radius), rng(seed) {
    
    //Constructing and placing all the moving objects first
    //Constructing the moving cars first
    for (int i=0; i<this->numOfMovingCars; i++) {
        //Generate random position for the moving vehicle
        Position randomCarPosition = rng.randomPosition(width, height);
        //Generate a random direction for the moving vehicle to head towards
        Direction randomCarDirection = rng.randomDirection();
        //Generate a random speed state (except STOPPED) for the moving vehicle to have
        SpeedState randomCarSpeed = rng.randomSpeed();
         auto car = make_unique<MovingCar>("MCAR" + to_string(i),
                                         randomCarPosition,
                                         randomCarSpeed,
                                         randomCarDirection,
                                         this, rng);
         addObject(move(car));
    }

    //Constructing the moving bikes likewise
    for (int i=0; i<this->numOfMovingBikes; i++) {
        //Generate random position for the moving vehicle
        Position randomBikePosition = rng.randomPosition(width, height);
        //Generate a random direction for the moving vehicle to head towards
        Direction randomBikeDirection = rng.randomDirection();
        //Generate a random speed state (except STOPPED) for the moving vehicle to have
        SpeedState randomBikeSpeed = rng.randomSpeed();
        auto bike = make_unique<MovingBike>("MBIKE" + to_string(i),
                                           randomBikePosition,
                                           randomBikeSpeed,
                                           randomBikeDirection,
                                           this, rng);
        addObject(move(bike));
    }

    //Constructing and placing all the stationary objects next
    //Constructing the stationary cars first
    for (int i=0; i<this->numOfStoppedCars; i++) {
        //Generate random position for the stationary vehicle
        Position randomCarPosition = rng.randomPosition(width, height);
        auto car = make_unique<StationaryVehicle>("SCAR" + to_string(i),
                                                 randomCarPosition,
                                                 this);
        addObject(move(car));
    }

    //Constructing the stop signs likewise
    for (int i=0; i<this->numOfStopSigns; i++) {
        //Generate random position for the sign
        Position randomSignPosition = rng.randomPosition(width, height);
        //Generate random type for the sign
        TrafficSignType randomSignType = rng.randomTrafficSignType();
        auto sign = make_unique<TrafficSign>("SIGN" + to_string(i),
                                            randomSignPosition,
                                            randomSignType,
                                            this);
        addObject(move(sign));
    }

    //Constructing the traffic lights
    for (int i=0; i<this->numOfTrafficLights; i++) {
        //Generate random position for the traffic light
        Position randomTrafficLightPosition = rng.randomPosition(width, height);
        //Generate random starting color for the traffic light
        TrafficLightColor randomTrafficLightColor = rng.randomTrafficLightColor();
        auto light = make_unique<TrafficLight>("TLIG" + to_string(i),
                                              randomTrafficLightPosition,
                                              randomTrafficLightColor,
                                              this);
        addObject(move(light));
    }

    //Creating the self driving vehicle
    //Generate random position for the self driving vehicle
    Position randomSelfDrivingVehiclePosition = rng.randomPosition(width, height);
    auto sdv = make_unique<SelfDrivingVehicle>("SDCAR",
                                               randomSelfDrivingVehiclePosition,
                                               this,
                                               mCT, targetPositions);
    addObject(move(sdv));

}

//Add Object
void GridWorld::addObject(unique_ptr<WorldObject> obj) {
    obj->setWorld(this);
    objects.push_back(move(obj));
}

//Update World
void GridWorld::update() {
    ++currentTick;
    for (size_t i = 0; i < objects.size(); ++i) {
        WorldObject* obj = objects[i].get();
        // Object updates
        obj->update();
    }
        // Clean up objects marked for removal
    auto it = remove_if(objects.begin(), objects.end(),
        [](const unique_ptr<WorldObject>& obj) {
            // Check if object is out of bounds
            GridWorld* world = obj->getWorld();
            if (world && !world->isInBounds(obj->getPosition())) {
                cout << "[-WORLD] Object " << obj->getId() 
                     << " at (" << obj->getPosition().getX() 
                     << "," << obj->getPosition().getY() 
                     << ") moved out of bounds." << endl;
                return true;
            }
            return false;
        });
    
    objects.erase(it, objects.end());
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

//Helpfull functions for the pov visualisation
//Functions to turn the information of the objects in the world to string
string directionToString (Direction dir) {
    switch(dir) {
        case Direction::NORTH: return "NORTH";
        case Direction::EAST: return "EAST";
        case Direction::SOUTH: return "SOUTH";
        default: return "WEST";
    }
};

string speedToString (SpeedState speed) {
    switch(speed) {
        case SpeedState::FULL_SPEED: return "FULL SPEED";
        case SpeedState::HALF_SPEED: return "HALF SPEED";
        default: return "STOPPED";
    }
};

//Function to visualise the grid
void GridWorld::renderer () const {
    
    //Create an empty grid
    vector<vector<char>> grid(height, vector<char>(width, '.'));

    //Fill the grid vector with all the objects
    for (const auto& obj : objects) {
        const Position& position = obj->getPosition();
        if (isInBounds(position)) { grid[position.getY()][position.getX()] = obj->getGlyph(); }
    }

    //Visualization Full
    if (currentTick == 1 || currentTick == numberOfTics) {
        //Print the visualisation of the grid
        for (int y=height-1; y>=0; y--) {
            for (int x=0; x<width; x++) {
                cout << grid[y][x] << ' ';
            }
            cout << '\n';
        }
    }
    //Visualization POV
    else {
        //Find the self driving vehicle
        SelfDrivingVehicle* vehicle = nullptr;
        for (const auto& obj : objects) {
            if (auto* sdv_ptr = dynamic_cast<SelfDrivingVehicle*>(obj.get())) {
                vehicle = sdv_ptr;
                break;
            }
        }

        //If there is no vehicle found end the visualization
        if (!vehicle) {
            cout << "[POV] No autonomous vehicle found!" << endl;
            return;
        }

        //Store the vehicle's information
        Position vehiclePosition = vehicle->getPosition();
        Direction vehicleDirection = vehicle->getDirection();
        SpeedState vehicleSpeed = vehicle->getSpeedState();

        cout << "\n===POV Visualization===" << endl;
        cout << "Vehicle: " << vehicle->getId() << " at ("
             << vehiclePosition.getX() << "," << vehiclePosition.getY()
             << ") heading towards the " << directionToString(vehicleDirection)
             << " going at " << speedToString(vehicleSpeed) << endl;

        //Helper for safe out of bounds drawing
        auto drawCell = [&](int x, int y) {
            if (x >= 0 && x < width && y >= 0 && y < height) { cout << grid[y][x] << ' ';}
            else { cout << '#' << ' '; }
        };

        //Around pov setting (a grid with radius (radius) with center the autonomus vehicle)
        if (povSetting == "around") {
            int half = radius/2 + 1;

            //Print the visualisation of the POV
            for (int y=vehiclePosition.getY() + half; y>= vehiclePosition.getY() - half; y--) {
                for (int x=vehiclePosition.getX() - half; x<=vehiclePosition.getX() + half; x++) {
                    drawCell(x, y);
                }
                cout << '\n';
            }
        }
        //Front pov setting (a grid with radius (radius) in front of the autonomus vehicle)
        else if (povSetting == "front") {
            int half = radius/2;

            switch (vehicleDirection) {
                case Direction::NORTH: {
                    for (int y=vehiclePosition.getY() + 1; y<= vehiclePosition.getY() + radius; y++) {
                        for (int x=vehiclePosition.getX() - half; x<=vehiclePosition.getX() + half; x++) {
                            drawCell(x, y);
                        }
                        cout << '\n';
                    }
                    break;
                }
                case Direction::SOUTH: {
                    for (int y=vehiclePosition.getY() - 1; y<= vehiclePosition.getY() - radius; y--) {
                        for (int x=vehiclePosition.getX() - half; x<=vehiclePosition.getX() + half; x++) {
                            drawCell(x, y);
                        }
                        cout << '\n';
                    }
                    break;
                }
                case Direction::EAST: {
                    for (int y=vehiclePosition.getY() - half; y<= vehiclePosition.getY() + half; y++) {
                        for (int x=vehiclePosition.getX() + 1; x<=vehiclePosition.getX() + radius; x++) {
                            drawCell(x, y);
                        }
                        cout << '\n';
                    }
                    break;
                }
                default: {
                    for (int y=vehiclePosition.getY() - half; y<= vehiclePosition.getY() + half; y++) {
                        for (int x=vehiclePosition.getX() - 1; x<=vehiclePosition.getX() - radius; x--) {
                            drawCell(x, y);
                        }
                        cout << '\n';
                    }
                    break;
                }
            }
        }
    }
}

//Getters for the height width and current tick of the world
int GridWorld::getWidth() const { return width; }
int GridWorld::getHeight() const { return height; }
int GridWorld::getCurrentTick() const { return currentTick; }
unsigned int GridWorld::getSeed() const { return seed; }
const RandomGenerators& GridWorld::getRandomGenerator() const { return rng; }