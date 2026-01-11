#pragma once

#include "../world/StaticObject.h"
#include <iostream>
#include "../common/enums.h"
#include "../common/utils.h"

static const int RED_DURATION = 4;
static const int GREEN_DURATION = 8;
static const int YELLOW_DURATION = 2;


class TrafficLight : public StaticObject {
private:
    TrafficLightColor color;
    int tickCount;  // Counts how many ticks have passed until current state

public:
    TrafficLight(const std::string& id, const Position& position, const TrafficLightColor& color);

    // overrides update of base class StaticObject
    void update (GridWorld& world) override;

    // override virtual getGlyph()
    char getGlyph() const override;

    // getters
    TrafficLightColor getColor() const { return color; }

};

