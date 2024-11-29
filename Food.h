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
        objPosArrayList* foodBucket;
        int size;
    
    public:
        Food(); 
        ~Food();
        Food(const Food& myFood); 
        Food& operator=(const Food& myFood); 

        void generateFood(objPosArrayList* blockOff, int xRange, int yRange);
        objPosArrayList const getFoodBucket();
        objPos const getFoodPos();
        int getSize();
};



#endif