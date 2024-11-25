#include "Food.h"
#include "MacUILib.h"
#include "GameMechs.h"

//Iteration 2B
Food::Food()
{
    foodPos.setObjPos(-10,-10,'*');
}

Food::~Food()
{

}

//Iteration 2B, steph
void Food::generateFood(objPos blockOff, int xRange, int yRange)
{
    int posX, posY;
    int xArr[xRange] = {0};
    int yArr[yRange] = {0};
    srand(time(NULL));
    int count = 0;

    while(count == 0)
    {
        posX = rand() % xRange;
        posY = rand() % yRange;
        if((xArr[posX] == 0 || yArr[posY] == 0)\
        && blockOff.pos->x != posX+1 && blockOff.pos->y != posY+1)
        {
            xArr[posX]++;
            yArr[posY]++;
            foodPos.pos->x = posX+1;
            foodPos.pos->y = posY+1;
            count++;
        }
    }
}

objPos const Food::getFoodPos()
{
    return foodPos;
}