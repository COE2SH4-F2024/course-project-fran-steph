#include "Food.h"
#include "GameMechs.h"

//Iteration 2B, steph
Food::Food()
{
    foodPos.setObjPos(-10,-10,'$'); // added lines -fran
    foodBucket = new objPosArrayList(); // added lines -fran
    foodBucket->insertHead(foodPos); // added lines -fran
    foodPos.setObjPos(-10,-10,'*');
    for(int i=0; i<4; i++) { // added lines -fran
        foodBucket->insertHead(foodPos); // added lines -fran
    } // added lines -fran
    size = 5; // added lines -fran
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
	delete[] foodBucket;
}

Food::Food(const Food& myFood)
{
    foodPos = myFood.foodPos;
    foodBucket = new objPosArrayList(); // added this? - fran
    // /*
    for(int i = 0; i < myFood.foodBucket->getSize(); i++)
    {
        foodBucket->insertTail(myFood.foodBucket->getElement(i));
    }
    size = myFood.size;
    // */
}

Food& Food::operator=(const Food& myFood)
{
    if(this != &myFood)
    {
        this->foodPos = myFood.foodPos;
        // delete foodBucket;
        // foodBucket = new objPosArrayList();
        // /*
        for(int i = 0; i < myFood.foodBucket->getSize(); i++) // changed 5 to myFood.foodBucket->getSize()
        {
            this->foodBucket->insertTail(myFood.foodBucket->getElement(i));
        }
        // */
    }
    return *this;
}

void Food::generateFood(objPosArrayList* blockOff, int xRange, int yRange)
{
    
    int posX, posY;
    srand(time(NULL));

    for(int i=0; i<foodBucket->getSize(); i++) {
        bool positionFound = false;

        while(!positionFound) {
            posX = rand() % (xRange-2);
            posY = rand() % (yRange-2);

            bool flag = false;
            for(int j = 0; j < blockOff->getSize(); j++) {
                if((posX == blockOff->getElement(j).pos->x) && (posY == blockOff->getElement(j).pos->y)) {
                    flag = true;
                    break;
                }
            }

            for(int j=0; j < foodBucket->getSize(); j++) {
                if((posX == foodBucket->getElement(j).pos->x) && (posY == foodBucket->getElement(j).pos->y)) {
                    flag = true;
                    break;
                }
            }
            if(!flag) {
                foodBucket->getElement(i).pos->x = posX;
                foodBucket->getElement(i).pos->y = posY;
                positionFound = true;
            }   
        }
    }
    // int count = 0;
    // while(count == 0)
    // {
    //     posX = rand() % (xRange-2);
    //     posY = rand() % (yRange-2);
    //     for(int i = 0; i < blockOff->getSize(); i++)
    //     {
    //         if(blockOff->getElement(i).pos->x != posX+1 && blockOff->getElement(i).pos->y != posY+1)
    //         {
    //             foodBucket->getElement(i).pos->x = posX + 1;
    //             foodBucket->getElement(i).pos->y = posY + 1;
    //             //foodPos.pos->x = posX+1; // UNCOMMENT FOR NORMAL PROJECT TO WORK
    //             //foodPos.pos->y = posY+1; // UNCOMMENT FOR NORMAL PROJECT TO WORK
    //             count++;
    //         }
    //     }
    // }
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
