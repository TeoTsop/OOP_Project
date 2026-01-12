#include "../../include/objects/TrafficLight.h"
#include <iostream>

TrafficLight::TrafficLight(const std::string& id, const Position& position, const TrafficLightColor& startColor)
    :StaticObject(
        id,
        (startColor == RED)   ? 'R' :
        (startColor == YELLOW) ? 'Y' :
        (startColor == GREEN)  ? 'G' : '?',
        position, 
        TRAFFIC_LIGHT),
        color(startColor), 
        tickCount(0)
{
    std::cout << "[+LIGHT: " << id << "] Initialized at ("
              << position.getX() << ", " << position.getY()
              << ") with color "
              << (color == RED ? "RED" :
                  color == YELLOW ? "YELLOW" : "GREEN") << "\n";
}

TrafficLightColor TrafficLight:: getColor() const { 
    return color;
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

