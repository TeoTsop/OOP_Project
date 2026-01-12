//Implementation for the parent class of the stationary vehicles, traffic lights and signs

#include "../../include/world/StaticObject.h"
#include "../../include/world/GridWorld.h" 

using namespace std;

//Constructor for a static object
StaticObject::StaticObject(const string& id, char glyph, const Position& pos, const ObjectType& ObjectType)
    : WorldObject(id, glyph, pos, ObjectType) {
//Empty
}

//Destructor a static object
StaticObject::~StaticObject () {}