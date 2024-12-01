#include <iostream>
#include "MacUILib.h"
#include "Player.h"
#include "GameMechs.h"
#include "Food.h"

#define DELAY_CONST 100000

// Define global pointers
Player *myPlayer; 
GameMechs *myGM; 
Food *myFood; 


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    // Instantiates player objects on the heap
    myGM = new GameMechs(); 
    myPlayer = new Player(myGM); 
    myFood = new Food(); 
}

void GetInput(void)
{
    //Collects asyncronous input from user
    myGM->collectAsyncInput();
}

void RunLogic(void)
{
    // Static int for condition to generate first food on gameboard only once
    static int hasInput = 0;

    // Update player direction and move snake
    objPosArrayList* playerPos = myPlayer -> getPlayerPos();
    myPlayer->updatePlayerDir(); 
    myPlayer->movePlayer(myFood); 
    
    //Generates the first food item on the gameboard after user begins to move player
    if(hasInput==0)
    {
        if(myGM->getInput()!='\0')
        {
            myFood->generateFood(playerPos,myGM->getBoardSizeX(), myGM->getBoardSizeY()); // iteration 1.3, fran
            hasInput++;
        }
    }
     
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); 

    // Get food and player position 
    objPosArrayList* playerPos = myPlayer -> getPlayerPos();
    objPosArrayList* foodPos = myFood->getFoodBucket();

    // Get board X and Y dimension
    int boardX = myGM->getBoardSizeX();
    int boardY = myGM->getBoardSizeY();

    // Iterates through each position on the board
    for(int row = 0; row < boardY; row++)
    {
        for(int col = 0; col < boardX; col++)
        {

            // If on the edge of the bord, print border ('#')
            if(row == 0 || row == boardY-1 || col == 0 || col == boardX-1) 
            {
                MacUILib_printf("%c", '#');
            }

            //Draws everything else inside the border
            else 
            {
                bool isOccupied = false; 
                
                // Iterates through each element in snake body
                for(int i=0; i < playerPos->getSize(); i++) 
                {

                    // If position has a snake element, draws player at it's location
                    if(row == playerPos->getElement(i).pos->y && col == playerPos->getElement(i).pos->x)
                    {
                        MacUILib_printf("%c",playerPos->getElement(i).symbol);
                        isOccupied = true;
                        break;
                    }
                }

                // If position is not occupied by snake, draws food where player isn't
                if(!isOccupied) 
                {
                    // If position is food
                    for(int i = 0; i < foodPos->getSize(); i++)
                    {
                        //Prints food at coordinates
                        if(row == foodPos->getElement(i).pos->y && col == foodPos->getElement(i).pos->x)
                        {
                            MacUILib_printf("%c", foodPos->getElement(i).symbol);
                            isOccupied = true;
                            break;
                        }
                    }
                }
                if(!isOccupied) { // if empty
                    MacUILib_printf("%c", ' ');
                }
            }
        }
        MacUILib_printf("%c", '\n');
    }

    //Keeps track of player score count
    MacUILib_printf("The Score is: %d\n", myGM->getScore());
    
    //Prints loser message if loseFlag is triggered and ends games
    if(myGM->getLoseFlagStatus())
    {
        MacUILib_printf("Player has Lost\n");
        MacUILib_Delay(50000);
        myGM-> setExitTrue();
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    // Removes objects off the heap
    delete myPlayer;
    delete myGM; 
    delete myFood; 

    MacUILib_uninit();
}
