#include "GameMechs.h"
#include "MacUILib.h"

//GameMechs, steph
GameMechs::GameMechs()
{
    //From tutorial 10, steph
    input = 0;
    exitFlag =false;
    loseFlag = false;
    score = 0;

    boardSizeX = 20;
    boardSizeY = 10;
    //end tutorial 10, steph
}

GameMechs::GameMechs(int boardX, int boardY)
{
    //From tutorial 10, steph
    input = 0;
    exitFlag =false;
    loseFlag = false;
    score = 0;

    boardSizeX = boardX;
    boardSizeY = boardY;
    //end tutorial 10, steph
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    //Nothing on the heap (no new), Tutoial 10, steph
    //Destructor empty for now, Tutorial 10, steph
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag; //Tutorial 10, steph
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag; //Iteration 1B, steph
}
    

char GameMechs::getInput()
{
    //Commented out for tutorial 11, steph
    /*
    //Tutorial 10, steph
    if(MacUILib_hasChar())
    {
        input = MacUILib_getChar();
    }
    //End Tutorial 10, steph

    //Iteration 1B, steph
    if(input==' ')
    {
        setExitTrue();
    }
    */

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
    return boardSizeX; //Tutorial 10, steph
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY; //Tutorial 10, steph
}


void GameMechs::setExitTrue()
{
    exitFlag = true; //Iteration 1B, steph
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    this->input = this_input; //Iteration 1B, steph
}

void GameMechs::clearInput()
{
    input = 0; //NULL, Iteration 1B, steph
}

// More methods should be added here
void GameMechs::collectAsyncInput()
{
    //Tutorial 11, steph
    if(MacUILib_hasChar())
    {
        input = MacUILib_getChar();
    }

    if(input==' ')
    {
        setExitTrue();
    }
}