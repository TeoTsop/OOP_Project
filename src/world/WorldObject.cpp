//Implementation of the functions in the base abstract class

#include <iostream>
#include <string> //In order to be able to use the string variable type
#include "../../include/world/WorldObject.h" //The header file from where the functions below will be called

using namespace std;

//Pass world as a parameter
GridWorld world;

//Constructor
WorldObject::WorldObject(const string& id, char glyph, const Position& pos,
                         const ObjectType& objectType)
    : id(id), glyph(glyph), position(pos), objectType(objectType) {
//Empty
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
WorldObject::~WorldObject() {}