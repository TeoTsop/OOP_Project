//Implementation of the functions in the base abstract class

#include <iostream>
#include <string> //In order to be able to use the string variable type
#include "../../include/world/WorldObject.h" //The header file from where the functions below will be called
#include "../../include/world/GridWorld.h" //The header file of the simulation's world the

using namespace std;

//Constructor
WorldObject::WorldObject(const string& id, char glyph, const Position& pos,
                         const ObjectType& objectType, GridWorld* world)
    : id(id), glyph(glyph), position(pos), objectType(objectType), world(world) {
//Empty
}

//Getters for the id, glyph, position, type of the world object, and world
const string& WorldObject::getId() const { return id; }
char WorldObject::getGlyph() const { return glyph; }
const ObjectType& WorldObject::getObjectType() const { return objectType; }
const Position& WorldObject::getPosition() const { return position; }
GridWorld* WorldObject::getWorld() const { return world; }

//Setter for the position
void WorldObject::setPosition (int x, int y) {
    Position newPosition(x,y);
    if (world && !world->isInBounds(newPosition)) {
        cout << "Position not in bounds!" << endl;
        return;
    }
    this->position = newPosition;
}

//Setter for the grid world
void WorldObject::setWorld(GridWorld* w) { world = w; }

//Destructor for the world object
WorldObject::~WorldObject() {}