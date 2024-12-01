#include "objPosArrayList.h"

// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.

// Constructor
objPosArrayList::objPosArrayList()
{
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP;
    aList = new objPos[ARRAY_MAX_CAP]; 
}

// Destructor to remove on the heap
objPosArrayList::~objPosArrayList()
{
    delete[] aList; 
}

int objPosArrayList::getSize() const 
{
    return listSize;
}

// If the list is not full, insert element thisPos at the front of the list and increase listSize
void objPosArrayList::insertHead(objPos thisPos)
{
    if(listSize == arrayCapacity) {
        return;
    }
    for(int i = listSize; i > 0; i--) {
        aList[i] = aList[i-1];
    }
    aList[0] = thisPos;
    listSize++;
}

// If the list is not full, insert element thisPos at the end of the list and increase listSize
void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize == arrayCapacity) {
        return;
    }
    aList[listSize] = thisPos;
    listSize++;
}

// If list is not empty, remove first element in list and decrease listSize
void objPosArrayList::removeHead()
{
    if(listSize == 0) {
        return;
    }
    for(int i = 0; i < listSize; i++) {
        aList[i] = aList[i+1];
    }
    listSize--;
}

// If list is not empty, remove last element in list and decrease listSize
void objPosArrayList::removeTail()
{
    if(listSize == 0) {
        return;
    }
    listSize--;
}

objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    return aList[listSize-1];
}

objPos objPosArrayList::getElement(int index) const
{
    return aList[index];
}

