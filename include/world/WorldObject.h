//Base abstract class

#pragma once

#include <string> //In order to be able to use the string variable type
#include "../common/position.h" //In order to be able to track the position of the moving vehicle
#include "../common/enums.h" //In order to use the enum ObjectType
#include "GridWorld.h" //In order to access an instance of the grid

//Forward declaration
class GridWorld;

class WorldObject {
    // Fields to be used by objects that belong to a sub-class of this class  
    protected:
        std::string id;                  //The id of the world object
        char glyph;                 //The glyph of the world object
        Position position;          //The position of the world object
        enum ObjectType objectType; //The type of the world object

    public:

        //Constructor for the world object
        WorldObject(const std::string& id, char glyph, const Position& pos, const ObjectType& ObjectType);
    
        //Getters for the id, position, glyph and type of each object
        const string& getId() const;
        const Position& getPosition() const;
        const ObjectType& getObjectType() const;
        char getGlyph() const;

        //Setter for the position
        void setPosition(int x, int y);

        //WorldObject is an abstract class therefore the update function will be called
        //by each one of the objects in the grid separately
        virtual void update() = 0;
        
        //Destructor for the world object
        virtual ~WorldObject();
};