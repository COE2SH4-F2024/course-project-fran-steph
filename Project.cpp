#include <iostream>
#include "MacUILib.h"
//#include "objPos.h"

#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

Player *myPlayer; //Global pointer meant to instantiate a player object on the heap, Tutorial 10, steph
GameMechs *myGM; //Tutorial 10, steph, iteration 1B, steph
//objPos *myGameBoard; //Iteration 0, steph

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
    //myGameBoard = new objPos(); //Iteration 0, steph

    //myGameBoard->initGameBoard(myGM->getBoardSizeX(), myGM->getBoardSizeY()); //Iteration 0, steph

}


void GetInput(void)
{
    //Iteration 1B, steph
    char input = myGM->getInput();
    myGM->setInput(input);
}

void RunLogic(void)
{
    //Iteration 1B, steph
    if(myGM->getInput()==' ')
    {
        myGM->setExitTrue();
    }
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); 

    //Tutorial 10, steph
    objPos playerPos = myPlayer -> getPlayerPos();
    //End, Tutorial 10, steph

    //Game board draw routine, iteration 0, steph
   // myGameBoard->drawGameBoard(myGM->getBoardSizeX(), myGM->getBoardSizeY(), playerPos);//, itemPos)

    
    //Iteration 1B, steph
    //For debugging
    myGM->incrementScore();
    MacUILib_printf("The Score is: %d\n", myGM->getScore());
    

    if(myGM->getInput() == 'a')
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
    //MacUILib_clearScreen();  commented out by steph

    delete myPlayer; //Tutorial 10, steph
    delete myGM; //Tutorial 10, steph
    /*
    for(int i; i < myGM->getBoardSizeY(); i++)
    {
        delete[] myGameBoard->gameBoard[i];
    }
    delete[] myGameBoard->gameBoard;
    */
    //delete myGameBoard;
    

    MacUILib_uninit();
}
