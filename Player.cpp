#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef; //Tutorial 10, steph
    myDir = STOP; //Tutorial 10, steph

    // more actions to be included
    //Tutorial 10, steph
    playerPos.pos->x = mainGameMechsRef -> getBoardSizeX()/2;
    playerPos.pos->y = mainGameMechsRef -> getBoardSizeY()/2;
    playerPos.symbol = '@';
    //End Tutorial 10, steph

}


Player::~Player()
{
    // delete any heap members here
    //no keyword 'new' in the constructor
    //leave destructor empty FOR NOW
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list, Tutorial 10, steph
    return playerPos;

}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef -> getInput(); //Tutorial 10, steph
        // PPA3 input processing logic
        //Dr. Athars code, Tutorial 10, steph
        switch(input)
        {   
            case 's':
            case 'S':
            if(myDir != DOWN && myDir != UP)
                myDir = DOWN;
                break;
            case 'a':
            case 'A':
            if(myDir != LEFT && myDir != RIGHT)
                myDir = LEFT;
                break;
            case 'd':
            case 'D':
            if(myDir != LEFT && myDir != RIGHT)
                myDir = RIGHT;
                break;
            case 'w':
            case 'W':
            if(myDir != DOWN && myDir != UP)
                myDir = UP;
                break;

            default:
                break;
        }

}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
}

// More methods to be added