#include "objPos.h"
//#include "MacUILib.h"

objPos::objPos()
{
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0; //NULL
}

objPos::objPos(int xPos, int yPos, char sym)
{
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Respect the rule of six / minimum four
// [TODO] Implement the missing special member functions to meet the minimum four rule
//iteration 0
objPos::objPos(const objPos &obj) //Copy Constructor, steph
{
    pos = new Pos;
    pos->x = obj.pos->x;
    pos->y = obj.pos->y;
    symbol = obj.symbol;
}

objPos& objPos::operator=(const objPos &obj) //Copy Assignment Operator, steph
{
    if(this != &obj)
    {
        this->pos->x = obj.pos->x;
        this->pos->y = obj.pos->y;
        this->symbol = obj.symbol;
    }
    return *this;
}

objPos::~objPos() //Destructor, steph
{
    delete pos;
}

void objPos::setObjPos(objPos o)
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

void objPos::setObjPos(int xPos, int yPos, char sym)
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

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
/*
//Initialize game board, iteration 0, steph
void objPos::initGameBoard(int rangeX, int rangeY)
{
    gameBoard = new char*[rangeY];
    for(int i = 0; i < rangeY; i++)
	{
		gameBoard[i] = new char[rangeX];
	}

    for(int i = 0; i < rangeY; i++)
    {
        for(int j = 0; j < rangeX; j++)
        {
            if(i == 0 || i == (rangeY)-1)
            {
                gameBoard[i][j] = '#';
            }
            else if(j == 0 || j == (rangeX)-1)
            {
                gameBoard[i][j] = '#';
            }
            else
            {
                gameBoard[i][j] = ' ';
            }
        }
    }
}

//Draw game board, iteration 0, steph
void objPos::drawGameBoard(int rangeX, int rangeY, objPos player)//, objPos itemPos)
{
    for(int i = 0; i < rangeY; i++)
    {
        for(int j = 0; j < rangeX; j++)
        {
            if(i == player.pos -> y && j == player.pos -> x)
            {
                gameBoard[i][j] = player.symbol;
            }
            else if(gameBoard[i][j] != '#')
            {
                gameBoard[i][j] = ' ';
            }
            for(int n = 0; n < 5; n++)
            {
                if(i == n+1 && j == n+2 && gameBoard[i][j] != '#') //if(i == item.pos->y && j == item.pos->x && gameBoard[i][j] != '#')
                {
                    gameBoard[i][j] = '*';//item.symbol;
                }
            }
            MacUILib_printf("%c",gameBoard[i][j]);  
        }
        MacUILib_printf("\n");
    }
}
*/