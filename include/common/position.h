//Coordinates and Manhattan Distance

#pragma once
#include <cstdlib> // For abs (absolute value) function

using namespace std;

class Position {
private:
    int x;
    int y;
public:
    //Constructor
    Position(int x, int y);
    
    //Equality Operator
    bool operator==(const Position& other) const; 
    
    //Manhattan Distance
    int ManDist(const Position& other);
    
    //Getters
    int getX() const;
    int getY() const;
    
    //Setters
    void setX(int newX);
    void setY(int newY);

    //Destructor
    ~Position();
};