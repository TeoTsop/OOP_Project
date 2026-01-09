//Parent for STOP signs, lights, parked cars

#pragma once
#include "WorldObject.h"
#include "../common/position.h"
#include <string>

class StaticObject : public WorldObject {
    // Constructor
    StaticObject(const std::string& id, char glyph, const Position& pos);

    // Virtual destructor
    virtual ~StaticObject() = default;

    // Update (overrides WorldObject)
    virtual void update (class GridWorld& world) override;

};


//Message for Kostas Kiras

//Ebala merika pragmata sto WorldObject kai logika tha sou halaei to static koitaje to