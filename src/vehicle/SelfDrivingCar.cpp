//Implementation file for the functions inside the self driving vehicle

#include "../../include/vehicle/SelfDrivingCar.h" //The header file from where the functions below will be called



SelfDrivingVehicle::SelfDrivingVehicle (const std::string& id, const Position& position,
                                        GridWorld* world, int minConfidenceThreshold,
                                        const std::vector<Position*>& targetPositions)
    : MovingObject(id, '@', position, ObjectType::AUTONOMUS_VEHICLE, SpeedState::STOPPED, Direction::EAST, world),
      minConfidenceThreshold(minConfidenceThreshold), targetPositions(targetPositions) {

    cout << "[+SDCAR] Starting at (" << position.getX() << ", " 
         << position.getY() << "), stopped, heading towards the east" << endl;

}

void SelfDrivingVehicle::update () {
    return;
}

SelfDrivingVehicle::~SelfDrivingVehicle () {

    cout << "[-SDCAR]" << endl;

}