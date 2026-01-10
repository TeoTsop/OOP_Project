#include <iostream>
#include <string>
#include "../../include/world/WorldObject.h"
#include "include/common/enums.h"

using namespace std;

// Constructor
WorldObject::WorldObject(const string& id, char glyph, const Position& pos,
                         ObjectType objectType)
    : id(id), glyph(glyph), position(pos), objectType(objectType) {
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