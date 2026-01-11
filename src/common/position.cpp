#include "../../include/common/position.h"

using namespace std;


Position::Position(int X=0, int Y=0):x(X), y(Y) {} 

bool Position::operator==(const Position& other) const {
    return x == other.getX() && y==other.getY();
}

int Position::ManDist(const Position& other) {
    return abs(x- other.x) + abs(y- other.y);
}

int Position::getX() const { return x; }
int Position::getY() const { return y; }

void Position::setX(int newX) { this->x = newX; }
void Position::setY(int newY) { this->y = newY; }

Position::~Position() {}