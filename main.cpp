#include <iostream>
#include <string>
#include <cstring>  //For strcmp
#include <vector>
#include <ctime>    //For the seed number

#include "..\include\common\position.h"
#include "..\include\world\GridWorld.h"
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

    for (size_t i=0; i<s.size(); i++) {
        if (isdigit(s[i]) == false) {
            return false;
        }
    }
    return true;

}

//Function to check if a string is of argument format by checking if they start with --
bool isArgument (const string& s) {
    return s.length() > 2 && s[0] == '-' && s[1] == '-';
}

//A ckeck to determine if the arguments provided are used correctly
bool checkArgumentValidity (int argumentPosition, int totalArguments, char* arguments[],
                            const string& argumentName, bool requiresValue = true) {

    //Check if the arument requires a value
    if (requiresValue) {
        //Check if a value can exist after the codenme (if the arguments end)
        if (argumentPosition + 1 >= totalArguments) {
            cout << "ERROR: Argument '" << argumentName << "' requires a value yet arguments end there!" << endl;
            return false;
        }

        string valueString = arguments[argumentPosition + 1];
        //Check if the next argument starts with "--" which is not a value
        if (valueString.length() > 2 && isArgument(valueString)) {
            cout << "ERROR: Argument '" << argumentName << "' requires a value not another codename!" << endl;
            return false;
        }

        //Check if the value is a valid number
        if (!numberCheck(valueString)) {
            cout << "ERROR: Argument '" << argumentName << "' requires a numeric value after it!" << endl;
            return false;
        }

        //Check if there is another value after it without purpose
        if (argumentPosition + 2 < totalArguments) {
            string nextAfterValue = arguments[argumentPosition + 2];
            if (nextAfterValue.length() > 0 && !isArgument(nextAfterValue)) {
                cout << "ERROR: Unexpected argument after '" << argumentName << " " << valueString << endl;
                return false;
            }
        }
    }

    //The argument is clear
    return true;

}

int main (int argc, char* argv[]) {

    cout << "|===== Starting Simulation Initialization =====|\n" << endl;

    //Parameters to be set before commencing the simulation
    unsigned int seedNumber = static_cast<int>(time(NULL));;
    int dimX = 40, dimY = 40;
    int numMovingCars = 3;
    int numMovingBikes = 4;
    int numParkedCars = 5;
    int numStopSigns = 2;
    int numTrafficLights = 2;
    int simulationTicks = 100;
//    int minConfidenceThreshold = 40;
    vector<Position*> targetPositions;

    //Check for help first
    if (argc > 1 && strcmp(argv[1], "--help") == 0) {
        printHelp();
        return 0;
    }

    int i = 1; //Ommiting the first argument which is "./"
    while (i<argc) { //Checking for the special codes that can alter the default settings of the simulation

        string currArg = argv[i];

        //Hanlde gps codename
        if (currArg == "--gps") {

            i++;

            //Proccess target coordinates
            while (i<argc && !isArgument(string(argv[i]))) {
                if (i+1 >= argc) {
                    cout << "ERROR: Incomplete target coordinate pair given!" << endl;
                    return -1;
                }

                //Target coordinates
                string xstr = argv[i];
                string ystr = argv[i+1];

                //Check if target positions are numbers
                if (!numberCheck(xstr) || !numberCheck(ystr)) {
                    cout << "ERROR: Target coordinates ( " << xstr << ", " << ystr << ") must be numbers!" << endl;
                    return -1;
                }

                int x = stoi(xstr);
                int y = stoi(ystr);

                //Check if target position is in bounds
                if (x<0 || x>=dimX || y<0 || y>= dimY) {
                    cout << "ERROR: Position (" << x << ", " << y <<") falls out of bounds!" <<
                         "Grid starts from 0 and ends in " << dimX-1 << " in the x axis and from 0 to "
                         << dimY-1 << "in the y axis" << endl;
                    return -1;
                }
                else { targetPositions.push_back(new Position(x,y)); }

                i+=2;
            }
        }

        //Handle help codename
        else if (currArg == "--help") {
            printHelp();
            return 0;
        }

        else {
            //Check to ensure current argument's structural validity
            if (!checkArgumentValidity(i, argc, argv, currArg)) {return -1;}

            int value = stoi(argv[i+1]);

            //Seed number codename
            if (currArg == "--seed") { seedNumber = value; }

            //Grid's horrizontal dimention codename
            else if (currArg == "--dimX") { dimX = value; }

            //Grid's latteral dimention codename
            else if (currArg == "--dimY") { dimY = value; }

            //Number of moving cars in the grid codename
            else if (currArg == "--numMovingCars") { numMovingCars = value; }

            //Number of moving bikes in the grid codename
            else if (currArg == "--numMovingBikes") { numMovingBikes = value; }

            //Number of parked cars in the grid codename
            else if (currArg == "--numParkedCars") { numParkedCars = value; }

            //Number of parked bikes in the grid codename
            else if (currArg == "--numStopSigns") { numStopSigns = value; }

            //Number of traffic lights in the grid codename
            else if (currArg == "--numTrafficLights") { numTrafficLights = value; }

            //Number of ticks the simulation will last
            else if (currArg == "--simulationTicks") { simulationTicks = value; }

            //Min confidence threshold codename
//            else if (currArg == "--minConfidenceThreshold") { minConfidenceThreshold = value; }

            //Case of wrongly written codename
            else {
                cout << "ERROR: The argument [ " << currArg << " ] is either wrongly written or invalid!" << endl;
                cout << "Use --help after the executable to see available options!" << endl;
                return -1;
            }

            i += 2;
        }
    }

    if (targetPositions.empty()) {
        cout << "ERROR: No target position given! Use [--gps <x1> <y1>] in order to give target coordinates!" << endl;
        return -1;
    }

    //Check for negative values
    if (seedNumber <= 0) {
        cout << "ERROR: Seed cannot be below or equal to zero!" << endl;
        return -1;
    }
    constexpr unsigned int unsignedIntegerMaxValue = 4294967295u;
    if (seedNumber > unsignedIntegerMaxValue) {
        cout << "ERROR: Seed number way too large. Why are you spamming numbers? Maximum is "
             << unsignedIntegerMaxValue << ", otherwise there will be issues in the object generation!"
             << endl;
        return -1;
    }
    if (dimX <= 0 || dimY <= 0) {
        cout << "ERROR: Grid dimentions must not be negative numbers!" << endl;
        return -1;
    }
    if (numMovingBikes < 0 || numMovingCars < 0 || numParkedCars < 0 || numTrafficLights < 0 ||
        numStopSigns < 0) {
        cout << "ERROR: Object counts cannot fall below 0!" << endl;
        return -1;
    }
    if (simulationTicks <= 0) {
        cout << "ERROR: How can there be a simulation if its ticks are 0 or less?" << endl;
        return -1;
    }

    cout << "\n|=====Simulation Parameters Summary=====|" << endl;
    cout << "Seed: " << seedNumber << endl;
    cout << "Grid dimentions:\n\tx: " << dimX << "\n\ty: " << dimY << endl;
    cout << "Moving cars: " << numMovingCars << endl;
    cout << "Moving bikes: " << numMovingBikes << endl;
    cout << "Stationary vehicles: " << numParkedCars << endl;
    cout << "Stop signs: " << numStopSigns << endl;
    cout << "Traffic lights: " << numTrafficLights << endl;
    cout << "Total ticks: " << simulationTicks << endl;
    cout << "Target Positions: " << targetPositions.size() << endl;
    cout << "|=========================================|" << endl;

    cout << "|=====Creating Grid=====|" << endl;

    //Create grid
    GridWorld* grid = new GridWorld(seedNumber, dimX, dimY, simulationTicks, numMovingCars, numMovingBikes, 
                                    numTrafficLights, numStopSigns, numParkedCars);
    //Run simulation
    while (grid->getCurrentTick() < simulationTicks) { 
        cout << "\n|=============== Tick: " << grid->getCurrentTick()+1 << " ===============|" << endl;
        grid->update();
        grid->renderer(); 
    }

    cout << "\n|=====Simulation Ended=====|\n" << endl;

    //Cleanup
    for (auto pos : targetPositions) { delete pos; }
    delete grid;


    cout << "\nSimulation Completed Succseefully!\n" << endl;

    return 0;
}