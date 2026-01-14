//Header file with usefull classes used throughout the project
//Contents:
//  Random generators for the starting:
//                              Position on the grid 
//                              Speed of the moving vehicles
//                              Direction of the moving vehicles
//                              Color for the traffic lights
//                              Type for the signs
//   The random generation has been done while utilising the seed of the game given in
//  the construction of the grid. For this purpose the library marsenne_twister_engine
//  (std::mt19937). The specifics of how the algorithms in the library work i am not
//  realy aware of so here are some links i read to better understand how to use it:
//  https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine.html
//  https://jazzy.id.au/2010/09/22/cracking_random_number_generators_part_3.html

#pragma once

#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include "position.h"
#include "enums.h"

class RandomGenerators {
    private:
        std::unique_ptr<std::mt19937> generator; //The geenrator for the random numbers
        unsigned int seed;                       //The seed of the world
        bool initialized;                        //Check if the generator has been initialized

        //Function to return if the generator has been initialized or not
        void checkInitialized() const {
            if (!initialized) {
                throw std::runtime_error ("Random system not initialized!"
                                          "Call initializeWithSeed() first!");
            }
        }

    public:
        //Constructor for random generator
        RandomGenerators (unsigned int seed);

        //Initialize randomizer with current seed
        void intializeWithSeed (unsigned int seed);

        //Function to get a random integer, double
        int randomInteger (int min, int max);
        double randomDouble (double min, double max);

        //Function to get a random position inside the grid
        Position randomPosition (int width, int height);

        //Function to get a random direction
        Direction randomDirection ();

        //Function to get a random speed
        SpeedState randomSpeed ();

        //Function to get random traffic light color
        TrafficLightColor randomTrafficLightColor ();

        //Function to get a random treffic sign type
        TrafficSignType randomTrafficSignType ();

        //Function to reset the randomizer
        void reset ();
};