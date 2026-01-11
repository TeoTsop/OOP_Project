#include "../../include/world/StaticObject.h"
#include "../../include/world/GridWorld.h" 

using namespace std;

// Constructor
StaticObject::StaticObject(const string& id, char glyph, const Position& pos, const ObjectType& ObjectType)
    : WorldObject(id, glyph, pos, ObjectType) {
}

// Update (Only traffic lights update, the rest remain in their position forever)
void StaticObject::update() {
}