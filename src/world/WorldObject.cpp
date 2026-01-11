#include <iostream>
#include <string>
#include "include/world/GridWorld.h"
#include "../../include/world/WorldObject.h"
#include "include/common/enums.h"

using namespace std;

//Pass world as a parameter
GridWorld world;

//Constructor
WorldObject::WorldObject(const string& id, char glyph, const Position& pos,
                         const ObjectType& objectType)
    : id(id), glyph(glyph), position(pos), objectType(objectType) {
    // Empty for now
}

//Getters for the id, glyph, position and type of the world object
const string& WorldObject::getId() const { return id; }
char WorldObject::getGlyph() const { return glyph; }
const ObjectType& WorldObject::getObjectType() const { return objectType; }
const Position& WorldObject::getPosition() const { return position; }

//Setter for the position
void WorldObject::setPosition (int x, int y) {
    Position newPosition(x,y);
    if (!world.isInBounds(newPosition)) { cout << "Position not in bounds!" << endl; return; }
    this->position = newPosition;
}

//Destructor for the world object
WorldObject::~WorldObject() {
    // Empty for now
}