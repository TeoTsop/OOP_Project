#pragma once

#include "../world/StaticObject.h"
#include <iostream>

static const int RED_DURATION = 4;
static const int GREEN_DURATION = 8;
static const int YELLOW_DURATION = 2;

enum class TrafficLightColor { RED, YELLOW, GREEN };

class TrafficLight : public StaticObject {
private:
    TrafficLightColor color;
    int tickCount;  // Counts how many ticks have passed until current state

public:
    TrafficLight(const std::string& id, const Position& position, TrafficLightColor startColor = TrafficLightColor::RED);

    // overrides update of base class StaticObject
    void update (GridWorld& world) override;

    // override virtual getGlyph()
    char getGlyph() const override;

    // getters
    TrafficLightColor getColor() const { return color; }
};

