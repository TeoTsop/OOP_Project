//Implementation file for the functions inside the self driving vehicle

#include "../../include/vehicle/SelfDrivingCar.h" //The header file from where the functions below will be called

using namespace std;

SelfDrivingVehicle::SelfDrivingVehicle (const std::string& id, const Position& position,
                                        GridWorld* world, int minConfidenceThreshold,
                                        const std::vector<Position*>& targetPositions)
    : MovingObject(id, '@', position, ObjectType::AUTONOMUS_VEHICLE, SpeedState::STOPPED, Direction::EAST, world),
      minConfidenceThreshold(minConfidenceThreshold), targetPositions(targetPositions) {

    cout << "[+SDCAR] Starting at (" << position.getX() << ", " 
         << position.getY() << "), stopped, heading towards the east" << endl;

}

void SelfDrivingVehicle::update () {
    
    //Create sensor objects
    CameraSensor camera;
    RadarSensor radar;
    LidarSensor lidar;

    //Call sense for every one of the sensors
    camera.sense(*(this->getWorld()), this->getPosition(), this->getDirection());
    radar.sense(*(this->getWorld()), this->getPosition(), this->getDirection());
    lidar.sense(*(this->getWorld()), this->getPosition(), this->getDirection());

    //Collect all the readings inside one vector
    vector<SensorReading> allReadings;
    //Include camera readings
    const auto& cameraReadings = camera.getReadings();
    allReadings.insert(allReadings.end(), cameraReadings.begin(), cameraReadings.end());
    //Include radar readings
    const auto& radarReadings = radar.getReadings();
    allReadings.insert(allReadings.end(), radarReadings.begin(), radarReadings.end());
    //Include lidar readings
    const auto& lidarReadings = camera.getReadings();
    allReadings.insert(allReadings.end(), lidarReadings.begin(), lidarReadings.end());

    //Get fusion data
    SensorFusionEngine fusionEngine;
    vector<SensorReading> fusedObjects = fusionEngine.fuseSensorData(allReadings, minConfidenceThreshold);

    //Clear the sensors
    camera.clear();
    radar.clear();
    lidar.clear();

    setSensorData(fusedObjects);

}

vector<SensorReading> SelfDrivingVehicle::getSensorData () { return this->sensorsData; }
void SelfDrivingVehicle::setSensorData (vector<SensorReading> sr) { sensorsData = sr; }


SelfDrivingVehicle::~SelfDrivingVehicle () {

    cout << "[-SDCAR]" << endl;

}