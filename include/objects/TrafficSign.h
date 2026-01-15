//Header file for the traffic signs

#pragma once

#include <string>
#include "../common/enums.h" //In order to use the TrafficSignType and ObjectType enums
#include "../world/StaticObject.h" //Included since the Static Object class is the parent class of the traffic signs

class TrafficSign : public StaticObject {
    private:
        TrafficSignType signType;
        std::string signText;
    public:
        //Constructor for the traffic sign
        TrafficSign(const std::string& id, const Position& position, TrafficSignType type, GridWorld* world);

        //Getter for the traffic sign type
        TrafficSignType getSignType() const;

        // Getter for the sign text (for Camera sensor)
        const string& getSignText() const;

        //Setter to set the sign text
        void setSignText (const string& text);

        //Function for world update (does nothing)
        void update ();

        //Destructor for the traffic sign
        ~TrafficSign ();
};
