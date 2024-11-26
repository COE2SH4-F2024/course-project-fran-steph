#include <iostream>
#include "MacUILib.h"
#include "Player.h"
#include "GameMechs.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

Player *myPlayer; //Global pointer meant to instantiate a player object on the heap, Tutorial 10, steph
GameMechs *myGM; //Tutorial 10, steph, iteration 1B, steph
Food *myFood; //Iteration 2B, steph

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

    myGM = new GameMechs(); //Tutorial 10, steph, iteration 1B, steph
    myPlayer = new Player(myGM); //Tutorial 10, steph
    myFood = new Food(); //iteration 2B, steph
}


void GetInput(void)
{
    //Iteration 1B, steph
    myGM->collectAsyncInput();
    
}

void RunLogic(void)
{
    //Iteration 2B, for debugging
    /*
    if(myGM->getInput()=='c')
    {
        myFood->generateFood(myPlayer->getPlayerPos()->getHeadElement(),myGM->getBoardSizeX(), myGM->getBoardSizeY()); // edited by fran Iteration 3
    }
    */
    objPosArrayList* playerPos = myPlayer -> getPlayerPos();
    myPlayer->updatePlayerDir(); // Iteration 1A, fran
    myPlayer->movePlayer(myFood); // Iteration 1A, fran
    //myPlayer->checkSelfCollision();
    
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

    //Tutorial 10, steph
    objPosArrayList* playerPos = myPlayer -> getPlayerPos(); // edited by fran iteration 3
    objPos foodPos = myFood -> getFoodPos();
    int boardX = myGM->getBoardSizeX();
    int boardY = myGM->getBoardSizeY();
    //End, Tutorial 10, steph

    for(int row = 0; row < boardY; row++)
    {
        for(int col = 0; col < boardX; col++)
        {
            if(row == 0 || row == boardY-1 || col == 0 || col == boardX-1) // If a border
            {
                MacUILib_printf("%c", '#');
            }
            else 
            {
                bool isPlayer = false; // determines if position has a player
                for(int i=0; i<playerPos->getSize(); i++) 
                {
                    if(row == playerPos->getElement(i).pos->y && col == playerPos->getElement(i).pos->x)
                    {
                        MacUILib_printf("%c",playerPos->getElement(i).symbol);
                        isPlayer = true;
                        break;
                    }
                }
                if(!isPlayer) 
                {
                    if(row == foodPos.pos->y && col == foodPos.pos->x) 
                    {
                        MacUILib_printf("%c", foodPos.symbol);
                        //For debugging, iteration 2B
                        myGM->clearInput();
                    } 
                    else 
                    { // if empty
                    MacUILib_printf("%c", ' ');
                    }
                }
            }
        }
        MacUILib_printf("%c", '\n');
    }

    //iteration 3.3, steph
    if(myGM->getLoseFlagStatus())
    {
        MacUILib_printf("Player has Lost\n");
        MacUILib_Delay(50000);
        myGM-> setExitTrue();
    }

    //Iteration 1B, steph
    //For debugging
    MacUILib_printf("%d,%d\n",myFood->getFoodPos().pos->x, myFood->getFoodPos().pos->y);
    MacUILib_printf("%d,%d\n",myPlayer->getPlayerPos()->getHeadElement().pos->x,myPlayer->getPlayerPos()->getHeadElement().pos->y);
    //myGM->incrementScore();
    MacUILib_printf("The Score is: %d\n", myGM->getScore());
    //MacUILib_printf("%d", myGM->getLoseFlagStatus());
    //MacUILib_printf("%d", myGM->getExitFlagStatus());
    /*
    if(myGM->getInput() == 'l')
    {
        MacUILib_printf("Player has Lost");
        MacUILib_Delay(500000);
        myGM-> setLoseFlag();
    }
    */
    
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
    delete myFood; //Iteration 2B, steph

    MacUILib_uninit();
}
