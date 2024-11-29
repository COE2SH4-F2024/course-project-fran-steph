#include "GameMechs.h"
#include "MacUILib.h"

//Default constructor
GameMechs::GameMechs()
{
    input = 0;
    exitFlag =false;
    loseFlag = false;
    score = 0;

    boardSizeX = 20;
    boardSizeY = 10;
    
}


//Specialized constructor
GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag =false;
    loseFlag = false;
    score = 0;

    boardSizeX = boardX;
    boardSizeY = boardY;
}

//Destructor
GameMechs::~GameMechs()
{
    
}

//Copy constructor
GameMechs::GameMechs(const GameMechs& myGame)
{
    input = myGame.input;
    exitFlag = myGame.exitFlag;
    loseFlag = myGame.loseFlag;
    score = myGame.score;
    boardSizeX = myGame.boardSizeX;
    boardSizeY = myGame.boardSizeY;
}

//Copy assignment constructor
GameMechs& GameMechs::operator=(const GameMechs& myGame)
{
    if(this != &myGame)
    {
        this->input = myGame.input;
        this->exitFlag = myGame.exitFlag;
        this->loseFlag = myGame.loseFlag;
        this->score = myGame.score;
        this->boardSizeX = myGame.boardSizeX;
        this->boardSizeY = myGame.boardSizeY;
    }
    return *this;
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag; 
}
    

char GameMechs::getInput()
{

    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score += 100;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX; 
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY; 
}


void GameMechs::setExitTrue()
{
    exitFlag = true; 
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    this->input = this_input; 
}

void GameMechs::clearInput()
{
    input = 0; 
}

void GameMechs::collectAsyncInput()
{
    if(MacUILib_hasChar())
    {
        input = MacUILib_getChar();
    }

    if(input==' ')
    {
        setExitTrue();
    }
}