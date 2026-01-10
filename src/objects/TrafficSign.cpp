#include "../../include/objects/TrafficSign.h"
#include <iostream>

TrafficSign::TrafficSign(const std::string& id, const Position& position, TrafficSignType type, const std::string& text): 
StaticObject(
    id,
    position,
    type == TrafficSignType::STOP        ? 'S' :
    type == TrafficSignType::SPEED_LIMIT ? 'L' :
    type == TrafficSignType::NO_ENTRY    ? 'N' :
    type == TrafficSignType::TOPONYM    ? 'T' : '?'),
    signType(type),
    text(text)   {
   
    std::cout << "[+SIGN: " << id << "] Created at ("
              << position.getX() << ", " << position.getY()
              << ") text=\"" << text << "\"\n";
}

TrafficSignType TrafficSign::getSignType() const {
    return signType;
}

const std::string& TrafficSign::getText() const {
    return text;
}

char TrafficSign::getGlyph() const {
    switch (signType) {
        case TrafficSignType::STOP:
            return 'S';
        case TrafficSignType::SPEED_LIMIT:
            return 'L';   // Limit
        case TrafficSignType::NO_ENTRY:
            return 'N';
        case TrafficSignType::TOPONYM:
            return 'T';
        default:
            return '?';
    }
}
