//Implementation for the parent class of the stationary vehicles, traffic lights and signs

#include "../../include/world/StaticObject.h" //The header file from where the functions below will be called
#include "../../include/world/GridWorld.h" //The header file of the simulation's world

using namespace std;

//Constructor for a static object
StaticObject::StaticObject(const string& id, char glyph, const Position& pos, const ObjectType& ObjectType, GridWorld* world)
    : WorldObject(id, glyph, pos, ObjectType, world) {
//Empty
}

//Destructor a static object
StaticObject::~StaticObject () {}