//Base abstract class (WorldObject)

#pragma once
#include <string>
#include "../common/position.h"
#include "../common/enums.h"

using namespace std;

class WorldObject {
    // Fields to be used by objects that belong to a sub-class of this class  
    protected:
        string id;                  //The id of the world object
        char glyph;                 //The glyph of the world object
        Position position;          //The position of the world object
        enum ObjectType objectType; //The type of the world object

    public:

        //Constructor for the world object
        WorldObject(const string& id, char glyph, const Position& pos, const ObjectType& ObjectType);
    
        //Getters for the id, position, glyph and type of each object
        const string& getId() const;
        const Position& getPosition() const;
        const ObjectType& getObjectType() const;
        virtual char getGlyph() const;

        //Setter for the position
        void setPosition(int x, int y);

        //WorldObject is an abstract class therefore the update function will be called
        //by each one of the objects in the grid separately
        virtual void update() = 0;
        
        //Destructor for the world object
        virtual ~WorldObject();
};