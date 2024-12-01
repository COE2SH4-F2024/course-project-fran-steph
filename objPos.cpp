#include "objPos.h"

// Default Constructor
objPos::objPos() 
{
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0; //NULL
}

//Specialized Constructor
objPos::objPos(int xPos, int yPos, char sym)
{
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

//Copy Constructor
objPos::objPos(const objPos &obj)
{
    pos = new Pos;
    pos->x = obj.pos->x;
    pos->y = obj.pos->y;
    symbol = obj.symbol;
}

//Copy Assignment Operator
objPos& objPos::operator=(const objPos &obj)
{
    if(this != &obj)
    {
        delete pos;
        pos = new Pos;
        pos->x = obj.pos->x;
        pos->y = obj.pos->y;
        symbol = obj.symbol;
    }
    return *this;
}

//Destructor
objPos::~objPos()
{
    delete pos;
}

// Setter
void objPos::setObjPos(objPos o)
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

// Setter
void objPos::setObjPos(int xPos, int yPos, char sym)
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Gets object
objPos objPos::getObjPos() const
{
    objPos returnPos;
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;
    
    return returnPos;
}

char objPos::getSymbol() const
{
    return symbol;
}

bool objPos::isPosEqual(const objPos* refPos) const
{
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    if(isPosEqual(refPos))
        return symbol;
    else
        return 0;
}
