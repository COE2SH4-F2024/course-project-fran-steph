#include <iostream>
#include "MacUILib.h"
#include "Player.h"
#include "GameMechs.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

Player *myPlayer; //Global pointer meant to instantiate a player object on the heap, Tutorial 10, steph
GameMechs *myGM; //Tutorial 10, steph, iteration 1B, steph
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

    while(myGM->getExitFlagStatus() == false && myGM->getLoseFlagStatus() == false)  
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

    myGM = new GameMechs(); //Tutorial 10, steph, iteration 1B, steph
    myPlayer = new Player(myGM); //Tutorial 10, steph
    myFood = new Food(); //iteration 2B
    
}


void GetInput(void)
{
    //Iteration 1B, steph
    myGM->collectAsyncInput();
}

void RunLogic(void)
{
    //Iteration 2B, for debugging
    if(myGM->getInput()=='c')
    {
        myFood->generateFood(myPlayer->getPlayerPos(),myGM->getBoardSizeX(), myGM->getBoardSizeY());
    }
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); 

    //Tutorial 10, steph
    objPos playerPos = myPlayer -> getPlayerPos();
    objPos foodPos = myFood -> getFoodPos();
    int boardX = myGM->getBoardSizeX();
    int boardY = myGM->getBoardSizeY();
    //End, Tutorial 10, steph

    for(int row = 0; row <= boardY; row++)
    {
        for(int col = 0; col <= boardX; col++)
        {
            if(row == 0 || row == boardY || col == 0 || col == boardX)
            {
                MacUILib_printf("%c", '#');
            }
            else if(row == playerPos.pos->y && col == playerPos.pos->x)
            {
                MacUILib_printf("%c",playerPos.symbol);
            }
            else if(row == foodPos.pos->y && col == foodPos.pos->x)
            {
                MacUILib_printf("%c", foodPos.symbol);
                //For debugging, iteration 2B
                myGM->clearInput();
            }
            else
            {
                MacUILib_printf("%c", ' ');
            }
        }
        MacUILib_printf("%c", '\n');
    }

    
    //Iteration 1B, steph
    //For debugging
    myGM->incrementScore();
    MacUILib_printf("The Score is: %d\n", myGM->getScore());
    if(myGM->getInput() == 'l')
    {
        MacUILib_printf("Player has Lost");
        MacUILib_Delay(500000);
        myGM-> setLoseFlag();
    }

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    //MacUILib_clearScreen();  Commented out by steph to test loseflag
    delete myPlayer; //Tutorial 10, steph
    delete myGM; //Tutorial 10, steph
    delete myFood;

    MacUILib_uninit();
}
