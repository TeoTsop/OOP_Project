#include "../../include/objects/TrafficLight.h"
#include <iostream>

TrafficLight::TrafficLight(const std::string& id, const Position& position, TrafficLightColor startColor)
    : StaticObject(id, position, 'R'), color(startColor), tickCount(0)
{
    std::cout << "[+LIGHT: " << id << "] Initialized at ("
              << position.getX() << ", " << position.getY()
              << ") with color "
              << (color == TrafficLightColor::RED ? "RED" :
                  color == TrafficLightColor::YELLOW ? "YELLOW" : "GREEN") << "\n";
}

// update state machine
void TrafficLight::update(GridWorld& world) {
    tickCount++;

    switch (color) {
        case TrafficLightColor::RED:
            if (tickCount >= RED_DURATION) {
                color = TrafficLightColor::GREEN;
                tickCount = 0;
            }
            break;

        case TrafficLightColor::GREEN:
            if (tickCount >= GREEN_DURATION) {
                color = TrafficLightColor::YELLOW;
                tickCount = 0;
            }
            break;

        case TrafficLightColor::YELLOW:
            if (tickCount >= YELLOW_DURATION) {
                color = TrafficLightColor::RED;
                tickCount = 0;
            }
            break;
    }

   
}

// Returns glyph according to color
char TrafficLight::getGlyph() const {
    switch (color) {
        case TrafficLightColor::RED:    return 'R';
        case TrafficLightColor::YELLOW: return 'Y';
        case TrafficLightColor::GREEN:  return 'G';
    }
    return '?'; 
}
