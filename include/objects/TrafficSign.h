#pragma once

#include "../world/StaticObject.h"
#include <string>


enum class TrafficSignType {
    STOP, 
    SPEED_LIMIT,
    NO_ENTRY,
    TOPONYM
};

class TrafficSign : public StaticObject {
private:
    TrafficSignType signType;
    std::string text;   // Sign texts (eg "STOP", "50", "NO ENTRY", "ATHENS")

public:
    TrafficSign(const std::string& id,
                const Position& position,
                TrafficSignType type,
                const std::string& text);

    TrafficSignType getSignType() const;
    const std::string& getText() const;

    char getGlyph() const override;
};
