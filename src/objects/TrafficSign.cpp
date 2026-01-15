//Implementation for the functions inside the traffic sign class

#include <iostream>
#include "../../include/objects/TrafficSign.h" //The header file from where the functions below will be called

using namespace std;

//Constructor for the traffic sign
TrafficSign::TrafficSign(const std::string& id, const Position& position, TrafficSignType type, GridWorld* world)
    : StaticObject( id,
                    (type == TrafficSignType::STOP)        ? 'S' :
                    (type == TrafficSignType::SPEED_LIMIT) ? 'L' :
                    (type == TrafficSignType::TURN_LEFT)   ? '<' :
                    (type == TrafficSignType::TURN_RIGHT)  ? '>' : '?', position, ObjectType::TRAFFIC_SIGN, world),
                    signType(type), signText ((type == TrafficSignType::STOP) ? "STOP" :
                                              (type == TrafficSignType::SPEED_LIMIT) ? "SREED_LIMIT" :
                                              (type == TrafficSignType::TURN_LEFT ? "TURN_LEFT" : "TURN_RIGHT")) {
   
    cout << "[+SIGN: " << id << "] Created at ("
         << position.getX() << ", " << position.getY()
         << ") of type "
         << (type ==  STOP? "STOP" :
             type == SPEED_LIMIT ? "SPEED_LIMIT" :
             type == TURN_LEFT ? "TURN_LEFT" : "TURN_RIGHT") << "\n";

}

//Function for world update (does nothing)
void TrafficSign::update () { return; }

//Getter for the type of the traffic sign
TrafficSignType TrafficSign::getSignType() const { return signType; }

//Getter for the sign text (for Camera sensor)
const string& TrafficSign::getSignText() const { return signText; }

//Setter for the traffic sign text
void TrafficSign:: setSignText (const string& text) { signText = text; }

//Destructor for the traffic sign
TrafficSign::~TrafficSign () {

    cout << "[-SIGN: " << id << "]" << endl;

}
