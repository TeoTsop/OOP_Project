#include "../../include/objects/TrafficSign.h"
#include <iostream>

TrafficSign::TrafficSign(const std::string& id, const Position& position, TrafficSignType type): 
StaticObject(id, getGlyph(), position, TRAFFIC_SIGN) {
   
    std::cout << "[+SIGN: " << id << "] Created at ("
              << position.getX() << ", " << position.getY()
              << "\"\n";
}

TrafficSignType TrafficSign::getSignType() const {
    return signType;
}


char TrafficSign::getGlyph() const {
    switch (signType) {
        case STOP:
            return 'S';
        case SPEED_LIMIT:
            return 'L';   // Limit
        case TURN_LEFT:
            return '<';
        case TURN_RIGHT:
            return '>';
        default:
            return '?';
    }
}

void TrafficSign::setGlyph()  {
    switch (signType) {
        case STOP:
            this->glyph= 'S';
        case SPEED_LIMIT:
            this->glyph= 'L';   // Limit
        case TURN_LEFT:
            this->glyph= '<';
        case TURN_RIGHT:
            this->glyph= '>';
        default:
            this->glyph= '?';
    }
}
