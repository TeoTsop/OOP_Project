//Header file for the traffic signs

#pragma once

#include <string>
#include "../common/enums.h" //In order to use the TrafficSignType and ObjectType enums
#include "../world/StaticObject.h" //Included since the Static Object class is the parent class of the traffic signs

class TrafficSign : public StaticObject {
    private:
        TrafficSignType signType;

    public:
        //Constructor for the traffic sign
        TrafficSign(const std::string& id, const Position& position, TrafficSignType type);

        //Getter for the traffic sign type
        TrafficSignType getSignType() const;

        //Function for world update (does nothing)
        void update ();

        //Destructor for the traffic sign
        ~TrafficSign ();
};
