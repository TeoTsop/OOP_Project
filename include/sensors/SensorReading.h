#pragma once
#include "../common/position.h"
#include "../common/enums.h"
#include <string>

// contains all possible sensor measurements (for all sensors).
class SensorReading {
private:
    ObjectType type;                //Type of the object detected
    Position position;              //Position of the object detected
    std::string objectId;           //Id of the object detected
    SensorType sensor;              //The sensor that completed the reading

    //These are optional, they may never be filled by the sensor
    TrafficLightColor trafficLight; //Color if the detected traffic light
    string signText;                //Text of the detected sign
    SpeedState speed;               //Speed the detected object has
    Direction direction;            //Direction the detected object is heading towards

    int distance;                   //Manhattan Distance from the autonomus vehicle to the object detected
    double readingConfidence;       //Each measurement will have its own confidence based on SensorType and the distance between sensor and the object 

public:
    //Constructor with default parameters, they are filled later in the sensors
    SensorReading(ObjectType t, const Position& pos, const std::string& id)
        : type(t), position(pos), objectId(id),
          trafficLight(TrafficLightColor::RED),
          signText(""),
          speed(SpeedState::STOPPED),
          direction(Direction::NORTH),
          distance(0),
          readingConfidence(0.0)
    {}

    // Getters / Setters
    ObjectType getObjectType() const { return type; }
    void setObjectType(ObjectType t) { type = t; }

    const Position& getPosition() const { return position; }
    void setPosition(const Position& p) { position = p; }

    const std::string& getObjectId() const { return objectId; }
    void setObjectId(const std::string& id) { objectId = id; }

    SensorType getSensorType() const { return sensor; }
    void setSensorType(SensorType s) { sensor = s; }

    TrafficLightColor getTrafficLightColor() const { return trafficLight; }
    void setTrafficLightColor(TrafficLightColor c) { trafficLight = c; }

    string getSignText() const { return signText; }
    void setSignText(string c) { signText = c; }

    SpeedState getSpeedState() const { return speed; }
    void setSpeedState(SpeedState s) { speed = s; }

    Direction getDirection() const { return direction; }
    void setDirection(Direction d) { direction = d; }

    int getDistance() const { return distance; }
    void setDistance(int d) { distance = d; }

    double getReadingConfidence() const { return readingConfidence; }
    void setReadingConfidence(double r) { readingConfidence = r; }
};