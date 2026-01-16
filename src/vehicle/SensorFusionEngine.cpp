//Sensor fusion engine algorithm implementation

#include "../../include/vehicle/SensorFusionEngine.h" //Included as the header file of the function below
#include <vector> //Included in order to use the vector
#include <unordered_map> //Included in order to use the unordered_map variable type
#include <algorithm> //Included to use the sort algorithm

using namespace std;

//Helper function to compute the weight of the sensor reading based on which sensors detected the object 
static double sensorBaseWeight (SensorType type) {
    switch (type) {
        //The lidar sensor can detect objects behind the autonomous vehicle which are irrelevant in the navigation
        //and that is why it has the lowest weight
        case SensorType::LIDAR: return 0.8;
        //The radar sensor is the most important and has the biggest weight since it detects objects straight ahead
        //of the autonomous vehicle
        case SensorType::RADAR: return 0.95;
        //The camera sensor is between the above two weight-wise since it checks the spaces in front of the aytonomous
        //vehicle however it can sense object left or right of the vehicle which can be irrelevant
        case SensorType::CAMERA: return 0.9;
    }
    return 0.5; //Default fallback
}

vector<SensorReading>SensorFusionEngine::fuseSensorData(const vector<SensorReading>& allReadings, double minConfidenceThreshold) const {

    vector<SensorReading> fusedResults; // Will be returned at the end

    // Fuses the readings of all the sensors for an object into one vector line
    unordered_map<string, vector<SensorReading>> groupedReadings;
    // Grouping of the objects with the same id
    for (const SensorReading& r : allReadings) {
        groupedReadings[r.getObjectId()].push_back(r);
    }

    // Fusion of all the sensor data for every object
    for (const auto& [objectId, readings] : groupedReadings) {

        if (readings.empty())
            continue;

        int sensorCount = readings.size();

        //Total weight of the object
        double totalWeight = 0.0;
        //Weighted confidence representing how certain the system is about the existence and classification of
        //the object
        double weightedConfidence = 0.0;
        //The most appropriate confidence for the correctness of the distance between the object and the self
        //driving car
        double weightedDistance = 0.0;

        for (const auto& r : readings) {
            //Check the weight of the sensor
            double sensorWeight = sensorBaseWeight(r.getSensorType());

            //Factor for the number of sensors recognizing the existence of the object
            //Case 1: All three sensors see the item. Therefore it is directly in front of it with a distance that
            //        varies from 1 to 4 spaces of the grid making the object of high priority
            double sensorNumberFactor = 1.0;
            //Case 2: Only one sensor has seen the object. That means it is either quite far from the vehicle
            //        (over 4 spaces in front of it and to the sides of the space in front of it) or behind it
            //        which are both cases that the item is not an immediate obstacle
            if (sensorCount == 1) sensorNumberFactor = 0.5;
            //Case 3: Two of the sensors have detected the item meaning it is in front of the vehicle either in the
            //        space mentioned in Case 2 or at most 7 places in front of the vehiclew which cleassifies it
            //        as a low to medium level obstacle
            else if (sensorCount == 2) sensorNumberFactor = 0.75;

            //Compute the final weight of the reading based on how trustworthy the sensor is and the number
            //of sensors the object has been detected by
            double sensorWeightSum = sensorWeight * sensorNumberFactor;

            weightedConfidence += r.getReadingConfidence() * sensorWeightSum;
            weightedDistance += r.getDistance() * sensorWeightSum;
            totalWeight += sensorWeightSum;

        }

        if (totalWeight == 0.0)
            continue;

        //Confidence based on all of the sensors combined
        double fusedConfidence = weightedConfidence/ totalWeight;
        //Distance certainty based on all the sensors combined
        int fusedDistance = static_cast<int>(weightedDistance / totalWeight);

        //If the object is below the minimum confidence threshold ignore it
        if (fusedConfidence < minConfidenceThreshold)
            continue;

        //The base checks for the most prominent classification reading and bases the allocation of the object's properties
        //on the particular sensor
        const SensorReading* base = &readings[0];
        for (const auto& r : readings) {
            if (r.getReadingConfidence() > base->getReadingConfidence()) { base = &r; }
        }

        //Creatin of the fused object. Here get stored the object properties taken from the best sensor and the quantitive characteristics
        //of the object based on the readings of all sensors (p.e. distance)
        SensorReading fused = *base;
        fused.setDistance(fusedDistance);
        fused.setReadingConfidence(fusedConfidence);

        for (const SensorReading& sr : readings) {
            // If it's a moving object and sr has an info about speedstate and direction, we add speedState and direction in fused accuracy fields
            if ((sr.getObjectType() == ObjectType::MOVING_CAR ||
                  sr.getObjectType() == ObjectType::MOVING_BIKE)) {

                if (sr.getSpeedState() != SpeedState::STOPPED &&
                     fused.getSpeedState() == SpeedState::STOPPED) {
                    fused.setSpeedState(sr.getSpeedState());
                }

                if (sr.getDirection() != Direction::NORTH &&
                    fused.getDirection() == Direction::NORTH) {
                    fused.setDirection(sr.getDirection());
                }
            }

            // If it's a traffic sign and sr has an info about that, we add speedState and direction in fused accuracy fields
            if (sr.getObjectType() == ObjectType::TRAFFIC_SIGN) {
                if (!sr.getSignText().empty() && fused.getSignText().empty()) {
                    fused.setSignText(sr.getSignText());
                }
            }

            // If it's a traffic light and sr has an info about that, we add speedState and direction in fused accuracy fields
            if (sr.getObjectType() == ObjectType::TRAFFIC_LIGHT) {
                if (sr.getTrafficLightColor() != TrafficLightColor::RED &&
                    fused.getTrafficLightColor() == TrafficLightColor::RED) {
                    fused.setTrafficLightColor(sr.getTrafficLightColor());
                }
            }
        }

        fusedResults.push_back(fused); // Adding the fused reading to the vector
    }

    //Sorting the readings from highest weight to lowest
    sort(fusedResults.begin(), fusedResults.end(), [](const SensorReading& a, const SensorReading& b) {
        return a.getReadingConfidence() > b.getReadingConfidence();
    });

    return fusedResults;
}