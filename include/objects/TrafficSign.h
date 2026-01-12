#pragma once

#include "../world/StaticObject.h"
#include "../common/enums.h"
#include <string>

class TrafficSign : public StaticObject {
private:
    TrafficSignType signType;

public:
    TrafficSign(const std::string& id,
                const Position& position,
                TrafficSignType type);

    TrafficSignType getSignType() const;
};
