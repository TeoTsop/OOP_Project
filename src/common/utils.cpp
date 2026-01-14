//

#include "../../include/common/utils.h"

#include <random>
#include <ctime>

namespace {
    //Internal random engine
    std::mt19937 rng;
}

namespace Utils {

    //Function to get a random integer
    int randomInteger (int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }

    //Function to get a random position inside the grid
    Position randomPosition (int width, int height) {
        int x = randomInteger(0, width-1);
        int y = randomInteger(0, height-1);
        return Position(x, y);
    }

    //Function to get a random direction
    Direction randomDirection () {
        int d = randomInteger(0, 3);
        switch (d) {
            case 0: return Direction::NORTH;
            case 1: return Direction::SOUTH;
            case 2: return Direction::EAST;
            default: return Direction::WEST;
        }
    }

    //Function to get a random speed
    SpeedState randomSpeed () {
        int d = randomInteger(0, 1);
        switch (d) {
            case 0: return SpeedState::HALF_SPEED;
            default: return SpeedState::FULL_SPEED;
        }
    }

    //Function to get random traffic light color
    TrafficLightColor randomTrafficLightColor () {
        int d = randomInteger(0, 2);
        switch (d) {
            case 0: return TrafficLightColor::RED;
            case 1: return TrafficLightColor::YELLOW;
            default: return TrafficLightColor::GREEN;
        }
    }

    TrafficSignType randomTrafficSignType () {
        int d = randomInteger(0,3);
        switch (d) {
            case 0: return TrafficSignType::STOP;
            case 1: return TrafficSignType::SPEED_LIMIT;
            case 2: return TrafficSignType::TURN_LEFT;
            default: return TrafficSignType::TURN_RIGHT;
        }
    }

}