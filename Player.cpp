#include "Player.h"
#include "MacUILib.h"

// Purpose: Methods for Player actions: update direction and movement, etc.

Player::Player(GameMechs* thisGMRef)// PPA3 input processing logic
{
    mainGameMechsRef = thisGMRef; 
    myDir = STOP; 

    playerPosList = new objPosArrayList(); // instantiates playerPosList on the heap
    objPos thisPos(mainGameMechsRef -> getBoardSizeX()/2, mainGameMechsRef -> getBoardSizeY()/2, '*');
    playerPosList->insertHead(thisPos); // Inserts first element to be in the middle of the board with symbol: '*'
}

// Destructor
Player::~Player() 
{
    delete[] playerPosList;
}

objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list, Tutorial 10, steph
    return playerPosList;
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef -> getInput(); 
        // Change player direction based on input and current direction
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

void Player::movePlayer(Food* thisFood)
{
    // PPA3 Finite State Machine logic
    objPos playerPos = playerPosList->getHeadElement(); // returns the head of the snake xPos and yPos

    // Variables for calculating next position
    int xPos = playerPos.pos->x;
    int yPos = playerPos.pos->y;
    
    getFood = thisFood;
    
    int foodSize = thisFood->getSize();
    int xFood[foodSize];
    int yFood[foodSize];

    //Initializes x and y food coordinates to xFood and yFood lists
    for(int i = 0; i < foodSize; i++)
    {
        xFood[i] = thisFood->getFoodBucket()->getElement(i).pos->x; 
        yFood[i] = thisFood->getFoodBucket()->getElement(i).pos->y; 
    }
    
    
    // Increments new x and y position based on direction
    switch(myDir)
    {
        case UP:
        yPos--;
        // Implementing Top Border Wraparound
        if(yPos == 0) {
        yPos = mainGameMechsRef -> getBoardSizeY()-2;
        }
        break;

        case DOWN:
        yPos++;
        // Implementing Bottom Border Wraparound
        if(yPos == mainGameMechsRef -> getBoardSizeY()-1) {
        yPos = 1;
        }
        break;

        case LEFT:
        xPos--;
        // Implementing Left Border Wraparound
        if(xPos == 0) {
        xPos = mainGameMechsRef -> getBoardSizeX()-2;
        }
        break;

        case RIGHT:
        xPos++;
        // Implementing Right Border Wraparound
        if(xPos == mainGameMechsRef -> getBoardSizeX()-1) {
        xPos = 1;
        }
        break;
    }

    // Collision Detection
    if(myDir!=STOP) 
    {
        /* 
        for(int i = 1; i < playerPosList->getSize(); i++)
        {
            objPos playerBody = playerPosList->getElement(i);
            if(playerBody.pos->x == xPos && playerBody.pos->y == yPos)
            {
                mainGameMechsRef->setLoseFlag();
                break;
            }
        }
        */

        //Checks if 'snake' has encoutered itself and sets loseFlag if it has
        if(checkSelfCollision(xPos,yPos)) 
        {
            mainGameMechsRef->setLoseFlag();
        }

        objPos nextObj(xPos,yPos,'*');
        bool isFood = false;

        //Detects if player has encoutered food and increments score and increase size if true
        //If new position is food, inserts new position to the head of the snake, increments score, and generates new food
        for(int i=0; i < foodSize; i++) {
            if(xPos == xFood[i] && yPos == yFood[i])
            {
                //Checks for normal food ('o') and applies normal food rewards
                if(getFood->getFoodBucket()->getElement(i).symbol == 'o')
                {
                    playerPosList->insertHead(nextObj);
                    getFood->generateFood(playerPosList, mainGameMechsRef->getBoardSizeX(), mainGameMechsRef->getBoardSizeY());
                    mainGameMechsRef->incrementScore(); // increase by 100 points
                    isFood = true;
                    break;
                }

                //Checks for special food ('$') and applies special food rewards
                else
                {
                    playerPosList->insertHead(nextObj);
                    playerPosList->removeTail();
                    
                    //Removes tail as long as player isn't already at size 1
                    if(playerPosList->getSize()>1)
                    {
                        playerPosList->removeTail();
                    }
                    getFood->generateFood(playerPosList, mainGameMechsRef->getBoardSizeX(), mainGameMechsRef->getBoardSizeY());

                    // Doubles the Score
                    int target = 2 * mainGameMechsRef->getScore();
                    while(mainGameMechsRef->getScore() != target)
                    mainGameMechsRef->incrementScore();
                    
                    isFood = true;
                    break;
                }
            }
        }
        // If no collision, keeps player moving while maintaining length
        if(!isFood) {

            // Insert the new position to the front of the list and remove the last element in the list
            playerPosList->insertHead(nextObj);
            playerPosList->removeTail();
        }
    } 
}

// Iterates through player elements and if any positions are the same
bool Player::checkSelfCollision(int xVal, int yVal) 
{
    for(int i = 1; i < playerPosList->getSize(); i++)
    {
        objPos playerBody = playerPosList->getElement(i);
        if(playerBody.pos->x == xVal && playerBody.pos->y == yVal)
        {
            return true;
        }
    }
    return false;
}