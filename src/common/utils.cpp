//File where the functions in the utils header file are described

#include <iostream>
#include "../../include/common/utils.h" //Include the header file from where the functions below will be called

using namespace std;

RandomGenerators::RandomGenerators (unsigned int newSeed) :
    seed(newSeed) {
    
    intializeWithSeed(newSeed);
}

//Initialize randomizer with current seed
void RandomGenerators::intializeWithSeed (unsigned int newSeed) {

    if (initialized) {
        cout << "[WARNING] Random generator already initialized! Current seed is: " << seed
             << ", ignoring new seed!" << endl;
    }

    //Creating the random generator based on the seed given
    generator = make_unique<std::mt19937>(newSeed);
    seed = newSeed;
    initialized = true;
}

//Function to get a random integer
int RandomGenerators::randomInteger (int min, int max) {

    checkInitialized();

    uniform_int_distribution<> dist(min, max);
    return dist(*generator);
}

//Function to get a random double
double RandomGenerators::randomDouble (double min, double max) {

    checkInitialized();

    uniform_int_distribution<> dist(min, max);
    return dist(*generator);
}

//Function to get a random position inside the grid
Position RandomGenerators::randomPosition (int width, int height) {

    int x = randomInteger(0, width-1);
    int y = randomInteger(0, height-1);

    return Position(x,y);

} 

//Function to get a random direction
Direction RandomGenerators::randomDirection () {
    //South=0, North=1, East=2, West=3
    return static_cast<Direction>(randomInteger(0,3));
}

//Function to get a random speed
SpeedState RandomGenerators::randomSpeed () {
    //Half Speed=1, Full Speed=2
    return static_cast<SpeedState>(randomInteger(1,2));
}

//Function to get random traffic light color
TrafficLightColor RandomGenerators::randomTrafficLightColor () {
    //Red=0, Yellow=1, Green=2
    return static_cast<TrafficLightColor>(randomInteger(0,3));
}

//Function to get a random treffic sign type
TrafficSignType RandomGenerators::randomTrafficSignType () {
    //Stor=0, Speed Limit=1, Turn Left=2, Turn Right=3
    return static_cast<TrafficSignType>(randomInteger(0,3));
}