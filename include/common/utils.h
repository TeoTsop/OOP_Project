//Random Starting Position / Direction / Speed Generator

#include "position.h"
#include "enums.h"

#pragma once

namespace Utils {
    
    //Function to get a random integer
    int randomInteger (int min, int max);

    //Function to get a random position inside the grid
    Position randomPosition (int width, int height);

    //Function to get a random direction
    Direction randomDirection ();

    //Function to get a random speed
    SpeedState randomSpeed ();

    //Function to get random traffic light color
    TrafficLightColor randomTrafficLightColor ();

    //Function to get a random treffic sign type
    TrafficSignType randomTrafficSignType ();
}