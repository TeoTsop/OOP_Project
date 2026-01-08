#include "../../include/world/StaticObject.h"
#include "../../include/world/GridWorld.h" 

using namespace std;

// Constructor
StaticObject::StaticObject(const string& id, const Position& pos, char glyph)
    : WorldObject(id, pos, glyph) {
}

// Update (Only traffic lights update, the rest remain in their position forever)
void StaticObject::update(GridWorld& world) {
}