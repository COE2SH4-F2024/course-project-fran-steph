#include "Food.h"
#include "GameMechs.h"


Food::Food()
{
    foodPos.setObjPos(-10,-10,'$'); 
    foodBucket = new objPosArrayList(); 
    foodBucket->insertHead(foodPos); 
    foodPos.setObjPos(-10,-10,'f');
    size = 5;
    for(int i=0; i<size-1; i++) 
    { 
        foodBucket->insertHead(foodPos); 
    }
}

Food::~Food()
{
	delete[] foodBucket;
}

Food::Food(const Food& myFood)
{
    foodPos = myFood.foodPos;
    foodBucket = new objPosArrayList(); 
    
    for(int i = 0; i < myFood.foodBucket->getSize(); i++)
    {
        foodBucket->insertHead(myFood.foodBucket->getElement(i)); 
    }
    size = myFood.size;
    
}

Food& Food::operator=(const Food& myFood)
{
    if(this != &myFood)
    {
        this->foodPos = myFood.foodPos;
        // delete foodBucket;
        this->foodBucket = new objPosArrayList(); 
        // /*
        for(int i = 0; i < myFood.foodBucket->getSize(); i++) 
        {
            this->foodBucket->insertHead(myFood.foodBucket->getElement(i));
        }
        // */
    }
    return *this;
}

void Food::generateFood(objPosArrayList* blockOff, int xRange, int yRange)
{
    
    int posX, posY;
    srand(time(NULL));
    int count = 0;

    //Generates normal food
    for(int i = 0; i < foodBucket->getSize()-2; i++) 
    {
        bool positionFound = false;

        //Repeatedly generates food until a free space (not a playe or other food) is found
        while(!positionFound) 
        {
            posX = rand() % (xRange-2);
            posY = rand() % (yRange-2);

            bool flag = false;
            //Checks if random coordinates coorespond to player
            for(int j = 0; j < blockOff->getSize(); j++) 
            {
                if((posX+1 == blockOff->getElement(j).pos->x) && (posY+1 == blockOff->getElement(j).pos->y)) 
                {
                    flag = true;
                    break;
                }
            }

            //Checks if random coordinates coorespond to other food
            for(int j=0; j < foodBucket->getSize(); j++) 
            {
                if((posX+1 == foodBucket->getElement(j).pos->x) && (posY+1 == foodBucket->getElement(j).pos->y)) 
                {
                    flag = true;
                    break;
                }
            }

            //Generates food if all conditions are met
            if(!flag) 
            {
                foodPos.setObjPos(posX+1,posY+1,'f');
                foodBucket->removeTail();
                foodBucket->insertHead(foodPos);
                positionFound = true;
            }   
        }
    }

    //Generates special food
    for(int i = 0; i < 2; i++) 
    {
        bool positionFound = false;

        //Repeatedly generates food until a free space (not a playe or other food) is found
        while(!positionFound) 
        {
            posX = rand() % (xRange-2);
            posY = rand() % (yRange-2);

            //Checks if random coordinates coorespond to player
            bool flag = false;
            for(int j = 0; j < blockOff->getSize(); j++) 
            {
                if((posX+1 == blockOff->getElement(j).pos->x) && (posY+1 == blockOff->getElement(j).pos->y)) 
                {
                    flag = true;
                    break;
                }
            }

            //Checks if random coordinates coorespond to other food
            for(int j=0; j < foodBucket->getSize(); j++) 
            {
                if((posX+1 == foodBucket->getElement(j).pos->x) && (posY+1 == foodBucket->getElement(j).pos->y)) 
                {
                    flag = true;
                    break;
                }
            }

            //Generates food if all conditions are met
            if(!flag) 
            {
                foodPos.setObjPos(posX+1,posY+1,'$');
                foodBucket->removeTail();
                foodBucket->insertHead(foodPos);
                positionFound = true;
            }   
        }
    }
}


objPosArrayList* Food::getFoodBucket()
{
    return foodBucket;
}

objPos const Food::getFoodPos()
{
    return foodPos;
}

int Food::getSize()
{
    return size;
}
