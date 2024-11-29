#include <iostream>
#include "MacUILib.h"
#include "Player.h"
#include "GameMechs.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000
//Global pointer meant to instantiate a player object on the heap
Player *myPlayer; 
GameMechs *myGM; 
Food *myFood; 

int hasInput = 0;


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
    myGM = new GameMechs(); //Tutorial 10, steph, iteration 1B, steph
    myPlayer = new Player(myGM); //Tutorial 10, steph
    myFood = new Food(); //iteration 2B, steph
}

void GetInput(void)
{
    //Collects asyncronous input from user
    myGM->collectAsyncInput();
}

void RunLogic(void)
{
    // Update player direction and move snake
    objPosArrayList* playerPos = myPlayer -> getPlayerPos();
    myPlayer->updatePlayerDir(); // iteration 1a, fran
    myPlayer->movePlayer(myFood); // iteration 1a, fran
    
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

    // Get board size, food, and player position 
    objPosArrayList* playerPos = myPlayer -> getPlayerPos(); // iteration 3.1, fran
    //objPosArrayList foodPos = myFood->getFoodBucket();
    objPos foodPos = myFood -> getFoodPos();
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
                bool isPlayer = false; 
                
                // Iterates through each element in snake body
                for(int i=0; i<playerPos->getSize(); i++) 
                {
                    // If position has a snake element, draws player at it's location
                    if(row == playerPos->getElement(i).pos->y && col == playerPos->getElement(i).pos->x)
                    {
                        MacUILib_printf("%c",playerPos->getElement(i).symbol);
                        isPlayer = true;
                        break;
                    }
                }

                // If position is not occupied by snake, draws food where player isn't
                if(!isPlayer) 
                {
                    // If position is food
                    //for(int i = 0; myFood->getSize(); i++)
                    //{
                        if(row == foodPos.pos->y && col == foodPos.pos->x) 
                        {
                            MacUILib_printf("%c", foodPos.symbol);
                        } 
                        else // if empty
                        { 
                        MacUILib_printf("%c", ' ');
                        }
                    //}
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
