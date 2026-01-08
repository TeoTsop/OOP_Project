#include <iostream>
#include <string>
#include "../../include/world/WorldObject.h"

using namespace std;

// Constructor
WorldObject::WorldObject(const string& id, const Position& pos, char glyph)
    : id(id), position(pos), glyph(glyph) {
    // Empty for now
}

// Destructor
WorldObject::~WorldObject() {
    // Empty for now
}

// Getters
const string& WorldObject::getId() const {
    return id;
}

const Position& WorldObject::getPosition() const {
    return position;
}

char WorldObject::getGlyph() const {
    return glyph;
}