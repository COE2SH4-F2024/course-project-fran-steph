#include "Food.h"
#include "GameMechs.h"

//Iteration 2B, steph
Food::Food()
{
    foodPos.setObjPos(-10,-10,'*');
}

Food::~Food()
{

}

void Food::generateFood(objPosArrayList* blockOff, int xRange, int yRange)
{
    int posX, posY;
    srand(time(NULL));
    int count = 0;
    
    while(count == 0)
    {
        posX = rand() % (xRange-2);
        posY = rand() % (yRange-2);
        for(int i = 0; i < blockOff->getSize(); i++)
        {
            if(blockOff->getElement(i).pos->x != posX+1 && blockOff->getElement(i).pos->y != posY+1)
            {
                foodPos.pos->x = posX+1;
                foodPos.pos->y = posY+1;
                count++;
            }
        }
    }
}

objPos const Food::getFoodPos()
{
    return foodPos;
}