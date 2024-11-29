#include "Food.h"
#include "GameMechs.h"

//Iteration 2B, steph
Food::Food()
{
    foodPos.setObjPos(-10,-10,'*');
    /*
    size = 5;
    foodBucket = new objPosArrayList[size];
    for(int i = 0; i < size-1; i++)
    {
        foodBucket[i].insertTail(foodPos);
    }
    foodPos.setObjPos(-10,-10,'$');
    foodBucket[size-1].insertTail(foodPos);
    */
}

Food::~Food()
{
	//delete[] foodBucket;
}

Food::Food(const Food& myFood)
{
    foodPos = myFood.foodPos;
    /*
    for(int i = 0; i < 5; i++)
    {
        foodBucket[i] = myFood.foodBucket[i];
    }
    */
}

Food& Food::operator=(const Food& myFood)
{
    if(this != &myFood)
    {
        this->foodPos = myFood.foodPos;
        /*
        for(int i = 0; i < 5; i++)
        {
            this->foodBucket[i] = myFood.foodBucket[i];
        }
        */
    }
    return *this;
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
                //foodBucket[count].getElement(i).pos->x = posX+1;
                //foodBucket[count].getElement(i).pos->y = posY+1;
                foodPos.pos->x = posX+1;
                foodPos.pos->y = posY+1;
                count++;
            }
        }
    }
}


objPosArrayList const Food::getFoodBucket()
{
    return *foodBucket;
}

objPos const Food::getFoodPos()
{
    return foodPos;
}

int Food::getSize()
{
    return size;
}
