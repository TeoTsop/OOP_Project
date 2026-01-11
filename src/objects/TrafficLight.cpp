#include "../../include/objects/TrafficLight.h"
#include <iostream>

TrafficLight::TrafficLight(const std::string& id, const Position& position, const TrafficLightColor& startColor)
    :StaticObject(id, chooseGlyph(), position, TRAFFIC_LIGHT), color(startColor), tickCount(0)
{
    std::cout << "[+LIGHT: " << id << "] Initialized at ("
              << position.getX() << ", " << position.getY()
              << ") with color "
              << (color == TrafficLightColor::RED ? "RED" :
                  color == TrafficLightColor::YELLOW ? "YELLOW" : "GREEN") << "\n";
}

// update state machine
void TrafficLight::update() {
    tickCount++;

    switch (color) {
        case RED:
            if (tickCount >= RED_DURATION) {
                color = GREEN;
                this->glyph='G';
                tickCount = 0;
            }
            break;

        case GREEN:
            if (tickCount >= GREEN_DURATION) {
                color = YELLOW;
                this->glyph='Y';
                tickCount = 0;
            }
            break;

        case YELLOW:
            if (tickCount >= YELLOW_DURATION) {
                color = RED;
                this->glyph='R';
                tickCount = 0;
            }
            break;
    }

   
}

// Returns glyph according to color
char TrafficLight::chooseGlyph() const {
    switch (color) {
        case RED:    return 'R';
        case YELLOW: return 'Y';
        case GREEN:  return 'G';
    }
    return '?'; 
}
