#ifndef OBJPOS_H
#define OBJPOS_H

// Not really a C++ thing
typedef struct 
{
    int x;
    int y;
} Pos;

class objPos
{
    public:
        Pos* pos;        
        char symbol;
        //char** gameBoard;

        objPos(); //Default Constructor 1/4
        objPos(int xPos, int yPos, char sym); //Specialized Contsructor
        
        // Respect the rule of six / minimum four
        // [TODO] Implement the missing special member functions to meet the minimum four rule
        //iteration 0
        objPos(const objPos &obj); //Copy Constructor 2/4, steph
        objPos& operator=(const objPos &obj); //Copy Assignment Operator 3/4, steph
        ~objPos(); //Destructor 4/4, steph

        void setObjPos(objPos o);    
        void setObjPos(int xPos, int yPos, char sym); 
        //void initGameBoard(int rangeX, int rangeY); 
        //void drawGameBoard(int rangeX, int rangeY, objPos player);//, objPos item);

        objPos getObjPos() const;
        char getSymbol() const;
        char getSymbolIfPosEqual(const objPos* refPos) const;
        
        bool isPosEqual(const objPos* refPos) const;
};

#endif