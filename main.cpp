#include <iostream>
#include <string>
#include <vector>
#include <ctime>    //For the seed number

#include "common\position.h"
#include "world\GridWorld.h"
using namespace std;

//Helper Function
void printHelp () {
    cout << " Self-Driving Car Simulation " << endl;
    cout << "Usage : " << endl;
    cout << " --seed <n>                        Random seed (default : current time) " << endl;
    cout << " --dimX <n>                        World width (default : 40) " << endl;
    cout << " --dimY <n>                        World height (default : 40) " << endl;
    cout << " --numMovingCars <n>               Number of moving cars (default : 3) " << endl;
    cout << " --numMovingBikes <n>              Number of moving bikes (default : 4) " << endl;
    cout << " --numParkedCars <n>               Number of parked cars (default : 5) " << endl;
    cout << " --numStopSigns <n>                Number of stop signs (default : 2) " << endl;
    cout << " --numTrafficLights <n>            Number of traffic lights (default : 2) " << endl;
    cout << " --simulationTicks <n>             Maximum simulation ticks (default : 100) " << endl;
    cout << " --minConfidenceThreshold <n>      Minimum confidence cutoff (default : 40) " << endl;
    cout << " --gps <x1> <y1> [ x2 y2 . . . ]   GPS target coordinates (required) " << endl;
    cout << " --help                            Show this help message" << endl << endl;
    cout << "Example usage : " << endl;
    cout << " ./main --seed 12 --dimY 50 --gps 10 20 32 15" << endl;
}

//Function to check if a string is actually a number
bool numberCheck (string s) {

    for (int i=0; i<s.size(); i++) {
        if (isdigit(s[i]) == false) {
            return false;
        }
    }
    return true;

}

//A ckeck to determine if the arguments provided are used correctly
bool checkArgumentValidity (int argumentPosition, char* arguments[]) {

    //Check if the argument following the codename is a number
    string s = arguments[argumentPosition+1]; //The argument after the codename
    if (numberCheck == false) {               //If said arument is not a number
        cout << "The arguments are structured wrongly!" << endl;
        return false;
    }

    //Check if the argument next to the number is another codename
    //since most codenames are described by one number
    //(The gps case is done separately)
    s = arguments[argumentPosition+2]; //The argumant after the number
    if (s[0] != '-') {                 //All string arguments start with '-'
        cout << "The arguments are structured wrongly!" << endl;
        return false;
    }
    //The argument is clear
    return true;

}

int main (int argc, char* argv[]) {

    //Parameters to be set before commencing the simulation
    int seedNumber = static_cast<int>(time(NULL));;
    int dimX = 40, dimY = 40;
    int numMovingCars = 3;
    int numMovingBikes = 4;
    int numParkedCars = 5;
    int numStopSigns = 2;
    int numTrafficLights = 2;
    int simulationTicks = 100;
    int minConfidenceThreshold = 40;



    int i = 1; //Ommiting the first argument which is "./"
    while (i<argc) { //Checking for the special codes that can alter the default settings of the simulation

        //Check to ensure current argument's structural validity
        if (checkArgumentValidity(i, argv) == false && argv[i] != "--gps" && argv[i] != "--help") {return -1;}

        //Seed number codename
        if (argv[i] == "--seed") { seedNumber = stoi(argv[i+1]); }
        //Grid's horrizontal dimention codename
        else if (argv[i] == "--dimX") { dimX = stoi(argv[i+1]); }
        //Grid's latteral dimention codename
        else if (argv[i] == "--dimY") { dimY = stoi(argv[i+1]); }
        //Number of moving cars in the grid codename
        else if (argv[i] == "--numMovingCars") { numMovingCars = stoi(argv[i+1]); }
        //Number of moving bikes in the grid codename
        else if (argv[i] == "--numMovingBikes") { numMovingBikes = stoi(argv[i+1]); }
        //Number of parked cars in the grid codename
        else if (argv[i] == "--numParkedCars") { numParkedCars = stoi(argv[i+1]); }
        //Number of parked bikes in the grid codename
        else if (argv[i] == "--numStopSigns") { numStopSigns = stoi(argv[i+1]); }
        //Number of traffic lights in the grid codename
        else if (argv[i] == "--numTrafficLights") { numTrafficLights = stoi(argv[i+1]); }
        //Number of ticks the simulation will last
        else if (argv[i] == "--simulationTicks") { simulationTicks = stoi(argv[i+1]); }
        //Min confidence threshold codename
        else if (argv[i] == "--minConfidenceThreshold") { minConfidenceThreshold = stoi(argv[i+1]); }
        //Target coordinates of sentient vehicle
        else if (argv[i] == "--gps") { break; }
        //Function to call the help menu
        else if (argv[i] == "--help") {
            printHelp();
            return 0;
        }
        //Case of wrongly written codename
        else {
            cout << "The argument [ " << argv[i] << " ] is either wrongly written or invalid!" << endl;
            return -1;
        }
        i += 2;
    }

    //All parameters are set! Now time to check and get the target position(s)!
    vector<Position> targetPositions;
    while (1) {
        if (checkArgumentValidity(*argv[i+1], argv) == false || checkArgumentValidity(*argv[i+2], argv) == false) {return -1;}
        Position newTargetPosition = new Position(argv[i+1], argv[i+2]); //Create a position object for the target coordinates
        if (newTargetPosition.getX() <= dimX && newTargetPosition.getY() <= dimY) {targetPositions.push_back(newTargetPosition);} //Chek if the position is in bounds of the grid
        else {cout << "Position (" << newTargetPosition.getX() << " , " << newTargetPosition.getY() << ") falls out of bounds. Please try again!" << endl;}
    }
    //Case of targed coordinated not given
    if (targetPositions.empty() == false) {
        cout << "Target coordinates for the vehicle are not given. Please restart the simulation!" << endl;
        return -1;
    }


    //NOTE TO FUTURE SELF AND KOSTAS
    //
    //HERE ADD THE CALLS OF THE SIMULATION
    //
    //IT WONT WORK OTHERWISE
 

}