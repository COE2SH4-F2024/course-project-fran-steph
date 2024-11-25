#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef; //Tutorial 10, steph
    myDir = STOP; //Tutorial 10, steph

    // more actions to be included
    //Tutorial 10, steph
    // playerPos.pos->x = mainGameMechsRef -> getBoardSizeX()/2;
    // playerPos.pos->y = mainGameMechsRef -> getBoardSizeY()/2;
    // playerPos.symbol = '@';
    //End Tutorial 10, steph
    playerPosList = new objPosArrayList();
    objPos thisPos(mainGameMechsRef -> getBoardSizeX()/2, mainGameMechsRef -> getBoardSizeY()/2, '@');

    //  comment/uncomment for testing snake movement without food, - fran
    // objPos pos1(11,5,'@');
    // objPos pos2(12,5,'@');
    // objPos pos3(13,5,'@');
    // objPos pos4(14,5,'@');
    // objPos pos5(15,5,'@');
    // playerPosList->insertHead(pos5);
    // playerPosList->insertHead(pos4);
    // playerPosList->insertHead(pos3);
    // playerPosList->insertHead(pos2);
    // playerPosList->insertHead(pos1);
    // end of testing

    playerPosList->insertHead(thisPos);
}


Player::~Player()
{
    // delete any heap members here
    //no keyword 'new' in the constructor
    //leave destructor empty FOR NOW
}

objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list, Tutorial 10, steph
    return playerPosList;
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
    objPos playerPos = playerPosList->getHeadElement(); // fran iteration 3
    static int xPos = playerPos.pos->x, yPos = playerPos.pos->y;
    
    switch(myDir)
    {
        case UP:
        yPos = playerPos.pos->y - 1;
        break;

        case DOWN:
        yPos = playerPos.pos->y + 1;
        break;

        case LEFT:
        xPos = playerPos.pos->x - 1;
        break;

        case RIGHT:
        xPos = playerPos.pos->x + 1;
        break;
    }
    // Heed to border wraparound
    if(playerPos.pos->x == 0) {
        xPos = mainGameMechsRef -> getBoardSizeX()-2;
    } else if(playerPos.pos->x == mainGameMechsRef -> getBoardSizeX()-1) {
        xPos = 1;
    }
    if(playerPos.pos->y == 0) {
        yPos = mainGameMechsRef -> getBoardSizeY()-2;
    } else if(playerPos.pos->y == mainGameMechsRef -> getBoardSizeY()-1) {
        yPos = 1;
    }
    if(myDir!=STOP) {
        objPos nextObj(xPos,yPos,'@');
        playerPosList->insertHead(nextObj);
        playerPosList->removeTail();
    }
}

// More methods to be added