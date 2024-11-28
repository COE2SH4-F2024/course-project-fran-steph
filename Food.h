#ifndef FOOD_H
#define FOOD_H
//Iteration 2B, steph
#include <cstdlib>
#include <time.h>
#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"

using namespace std;

class Food
{
    private:
        objPos foodPos;
    
    public:
        Food(); 
        ~Food();

        void generateFood(objPosArrayList* blockOff, int xRange, int yRange);
        objPos const getFoodPos();
};



#endif