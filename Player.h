#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

class Player
{
    
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef);
        ~Player();

        objPosArrayList* getPlayerPos() const; // Upgrade this in iteration 3
        void updatePlayerDir();
        void movePlayer(Food* thisFood);
        bool checkSelfCollision(int xVal, int yVal); // Added Method

    private:
        objPosArrayList* playerPosList; // Upgrade this in iteration 3     
        enum Dir myDir;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
        Food* getFood; 

};

#endif