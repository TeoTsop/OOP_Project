//Header file for the moving bikes

#include "common/enums.h" //In order to use the enums ObjectType, Direction, SpeedState
#include "common/position.h" //In order to be able to trach the position of the moving vehicle
#include "world/MovingObject.h" //Included since the Moving Object class is the parent class of the moving cars

#pragma once

class MovingBike : public MovingObject {

    MovingBike (const std::string& id, char glyph, Position position,
               ObjectType objectType, SpeedState speedState,
               Direction direction);

    void update (GridWorld& world) override;

    ~MovingBike ();

};