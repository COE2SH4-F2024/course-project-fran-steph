#include "Player.h"
#include "MacUILib.h"


Player::Player(GameMechs* thisGMRef)// PPA3 input processing logic)
{
    mainGameMechsRef = thisGMRef; 
    myDir = STOP; 

    playerPosList = new objPosArrayList(); // instantiates playerPosList on the heap
    objPos thisPos(mainGameMechsRef -> getBoardSizeX()/2, mainGameMechsRef -> getBoardSizeY()/2, '@');
    playerPosList->insertHead(thisPos); // Inserts first element to be in the middle of the board with symbol: '@'
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
    int xFood = getFood->getFoodPos().pos->x, yFood = getFood->getFoodPos().pos->y;
    //int foodSize = thisFood->getSize();
    //int xFood[foodSize];
    //int yFood[foodSize];
    /*
    for(int i = 0; i < foodSize; i++)
    {
        xFood[i] = thisFood->getFoodBucket().getElement(i).pos->x;
        yFood[i] = thisFood->getFoodBucket().getElement(i).pos->y;
    }
    */
    // Increments new x and y position based on direction
    switch(myDir)
    {
        case UP:
        yPos--;
        // Heed Wraparound
        if(yPos == 0) {
        yPos = mainGameMechsRef -> getBoardSizeY()-2;
        }
        break;

        case DOWN:
        yPos++;
        // Heed Wraparound
        if(yPos == mainGameMechsRef -> getBoardSizeY()-1) {
        yPos = 1;
        }
        break;

        case LEFT:
        xPos--;
        // Heed Wraparound
        if(xPos == 0) {
        xPos = mainGameMechsRef -> getBoardSizeX()-2;
        }
        break;

        case RIGHT:
        xPos++;
        // Heed Wraparound
        if(xPos == mainGameMechsRef -> getBoardSizeX()-1) {
        xPos = 1;
        }
        break;
    }

    if(myDir!=STOP) 
    {
        
        //Checks if 'snake' has encoutered itself and sets loseFlag if it has
        for(int i = 1; i < playerPosList->getSize(); i++)
        {
            objPos playerBody = playerPosList->getElement(i);
            if(playerPos.isPosEqual(&playerBody)) // Previously if(playerBody.pos->x == playerPos.pos->x && playerBody.pos->y == playerPos.pos->y)
            {
                mainGameMechsRef->setLoseFlag();
                break; // added break for efficiency
            }
        }
        objPos nextObj(xPos,yPos,'@'); // object for next position
        
        //for(int i = 0; i < foodSize; i++)
        //{
        //Detects if player has encoutered food and increments score and increase size if true
        //If new position is food, inserts new position to the head of the snake, increments score, and generates new food
        if(xPos == xFood && yPos == yFood)
        {
            playerPosList->insertHead(nextObj);
            getFood->generateFood(playerPosList, mainGameMechsRef->getBoardSizeX(), mainGameMechsRef->getBoardSizeY());
            mainGameMechsRef->incrementScore();
        }
        
        //Keeps player moving while mainting length
        else
        {
            // fran, iteration 3.1
            // Insert the new position to the front of the list and remove the last element in the list
            playerPosList->insertHead(nextObj);
            playerPosList->removeTail();
        }
        //}
    } 
    
    
}

