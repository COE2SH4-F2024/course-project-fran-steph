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
        Food(); //1/4
        ~Food(); //2/4
        

        void generateFood(objPos blockOff, int xRange, int yRange);
        objPos const getFoodPos();
};



#endif