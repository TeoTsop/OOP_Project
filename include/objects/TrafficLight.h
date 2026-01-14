//Header file for the traffic lights

#pragma once

#include <iostream>
#include "../common/enums.h" //In order to use the TrafficLigthColor and ObjectType enums
#include "../world/StaticObject.h" //Included since the Static Object class is the parent class of the traffic lights

//The duration of each light (standard)
static const int RED_DURATION = 4;
static const int GREEN_DURATION = 8;
static const int YELLOW_DURATION = 2;

//The class for the traffic lights
class TrafficLight : public StaticObject {
    private:
        TrafficLightColor color;    //The color of the traffic light
        int tickCount;              //Counts how many ticks have passed since the start of the current state

    public:
        //Constructor for the traffic light
        TrafficLight(const std::string& id, const Position& position, const TrafficLightColor& color, GridWorld* world);

        //Function to update the color of the traffic light
        //Overrides the function in the base class Static Object
        void update () override;

        //Getter for the current color of the traffic light
        TrafficLightColor getColor() const;

        //Destructor for the taffic light
        ~TrafficLight ();
};

