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

    //Initialing game characteristiccs, food, player and mechanics
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
    objPosArrayList* playerPos = myPlayer -> getPlayerPos();
    myPlayer->updatePlayerDir(); // Iteration 1A, fran
    myPlayer->movePlayer(myFood); // Iteration 1A, fran
    
    //Generates the first food item on the gameboard after user begins to move player
    if(hasInput==0)
    {
        if(myGM->getInput()!='\0')
        {
            myFood->generateFood(playerPos,myGM->getBoardSizeX(), myGM->getBoardSizeY()); // edited by fran Iteration 3
            hasInput++;
        }
    }
     
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); 

    objPosArrayList* playerPos = myPlayer -> getPlayerPos(); // edited by fran iteration 3
    //objPosArrayList foodPos = myFood->getFoodBucket();
    objPos foodPos = myFood->getFoodPos();
    int boardX = myGM->getBoardSizeX();
    int boardY = myGM->getBoardSizeY();

    //Draws gameboard, player, and food
    for(int row = 0; row < boardY; row++)
    {
        for(int col = 0; col < boardX; col++)
        {
            //Draws game border
            if(row == 0 || row == boardY-1 || col == 0 || col == boardX-1) // If a border
            {
                MacUILib_printf("%c", '#');
            }
            //Draws everything else inside the border
            else 
            {
                bool isPlayer = false; // determines if position has a player
                for(int i=0; i<playerPos->getSize(); i++) 
                {
                    //Draws player at it's location
                    if(row == playerPos->getElement(i).pos->y && col == playerPos->getElement(i).pos->x)
                    {
                        MacUILib_printf("%c",playerPos->getElement(i).symbol);
                        isPlayer = true;
                        break;
                    }
                }
                //Draws food where player isn's
                if(!isPlayer) 
                {
                    //for(int i = 0; myFood->getSize(); i++)
                    //{
                        if(row == foodPos.pos->y && col == foodPos.pos->x) 
                        {
                            MacUILib_printf("%c", foodPos.symbol);
                        } 
                        else 
                        { // if empty
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
    delete myPlayer; 
    delete myGM; 
    delete myFood; 

    MacUILib_uninit();
}
