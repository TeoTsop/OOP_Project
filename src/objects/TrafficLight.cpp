//Implementation for the functions inside the traffic light class

#include <iostream>
#include "../../include/objects/TrafficLight.h" //The header file from where the functions below will be called

using namespace std;

//Constructor for the traffic lights
TrafficLight::TrafficLight(const std::string& id, const Position& position, const TrafficLightColor& startColor, GridWorld* world)
    : StaticObject( id, 
                    (startColor == TrafficLightColor::RED)    ? 'R' :
                    (startColor == TrafficLightColor::YELLOW) ? 'Y' :
                    (startColor == TrafficLightColor::GREEN)  ? 'G' : '?',
                    position, ObjectType::TRAFFIC_LIGHT, world), color(startColor), tickCount(0) {

    cout << "[+LIGHT: " << id << "] Initialized at ("
         << position.getX() << ", " << position.getY()
         << ") with color "
         << (color == RED ? "RED" :
             color == YELLOW ? "YELLOW" : "GREEN") << "\n";
}



//Update the state of the object
void TrafficLight::update() {
    tickCount++;

    //Based on the current state of the traffic light and the ticks passed after its last change
    //judge wether its color should be updated
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

//Getter for the traffic light color
TrafficLightColor TrafficLight::getColor() const { return color; }

//Destructor for the traffic light
TrafficLight::~TrafficLight () {

    cout << "[-LIGHT: " << id << "]" << endl;

}