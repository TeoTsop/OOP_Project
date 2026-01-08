//Base abstract class (WorldObject)

#pragma once
#include <string>
#include "../common/position.h"

using namespace std;

class GridWorld; // forward declaration

class WorldObject {
// Fields to be used by objects that belong to a sub-class of this class  
protected:
    string id;
    Position position;
    char glyph;

public:
    WorldObject(const string& id, const Position& pos, char glyph);
    virtual ~WorldObject();
    virtual void update(GridWorld& world) = 0; // WorldObject is an abstract class
    
    // Getters
    const string& getId() const;
    const Position& getPosition() const;
    char getGlyph() const;
};