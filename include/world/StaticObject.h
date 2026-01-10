//Parent for STOP signs, lights, parked cars

#pragma once
#include "WorldObject.h"
#include "../common/position.h"
#include <string>

class StaticObject : public WorldObject {
public:
    // Constructor
    StaticObject(const std::string& id, const Position& pos, char glyph);

    // Virtual destructor
    virtual ~StaticObject() = default;

    // Update (overrides WorldObject)
    virtual void update(class GridWorld& world) override;

};