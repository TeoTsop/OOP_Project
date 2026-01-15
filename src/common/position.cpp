//Implementation of the functions in the position header file

#include "../../include/common/position.h"

using namespace std;


Position::Position(int X=0, int Y=0):x(X), y(Y) {} 

bool Position::operator==(const Position& other) const {
    return x == other.getX() && y==other.getY();
}

int Position::ManDist(const Position& other) const {
    return abs(x- other.x) + abs(y- other.y);
}

Position Position::moveInDirection(Direction dir, int step) const {
    switch(dir) {
        case Direction::NORTH: return Position(x, y+step);
        case Direction::SOUTH: return Position(x, y-step);
        case Direction::EAST:  return Position(x+step, y);
        case Direction::WEST:  return Position(x-step, y);
        default:               return *this; //In case anything goes wrong
    }
}

int Position::getX() const { return x; }
int Position::getY() const { return y; }

void Position::setX(int newX) { this->x = newX; }
void Position::setY(int newY) { this->y = newY; }

Position::~Position() {}