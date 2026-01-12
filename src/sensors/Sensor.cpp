#include "../../include/sensors/Sensor.h"
using namespace std;


// Constructor of base class Sensor
Sensor::Sensor() {}

// Getters
const vector <const WorldObject*>& Sensor:: getDetectedObjects() const { return detectedObjects; }
const vector <Position>& Sensor:: getDetectedPositions() const { return detectedPositions; }