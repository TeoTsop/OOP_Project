#include "../../include/objects/TrafficSign.h"
#include <iostream>

TrafficSign::TrafficSign(const std::string& id, const Position& position, TrafficSignType type): 
StaticObject(
    id,
    (type == STOP)        ? 'S' :
    (type == SPEED_LIMIT) ? 'L' :
    (type == TURN_LEFT)   ? '<' :
    (type == TURN_RIGHT)  ? '>' : '?',
    position,
    TRAFFIC_SIGN),
    signType(type) {
   
    std::cout << "[+SIGN: " << id << "] Created at ("
              << position.getX() << ", " << position.getY()
              << ") of type "
              << (type ==  STOP? "STOP" :
                  type == SPEED_LIMIT ? "SPEED_LIMIT" :
                  type == TURN_LEFT ? "TURN_LEFT" : "TURN_RIGHT") << "\n";
}

TrafficSignType TrafficSign::getSignType() const {
    return signType;
}


