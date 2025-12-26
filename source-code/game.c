#include <gb/gb.h>
#include <stdio.h>
#include "gamebuilder.h"
#include "elementsbuilder.h"
#include "background.h"

#define LEVEL_1_IDX 1
#define STEP 2

void run() {

    BYTE END = FALSE;
    BYTE BOOM = FALSE;


    setupPlayer();

    //for(int i = LEVEL_1_IDX; (i<=LEVEL_5_IDX && !END); i++) {
    launchLevel(LEVEL_1_IDX);
    loadElementsForLevel(LEVEL_1_IDX);
    
    
    int score = 1;

    ElementType *player = getElement(PLAYER_ID);


    while (!END) {

        //SET SCORE PLAYER
        setHUD(player->scores, player->lives);
        
        //DELAY
        performantDelay(STEP);
        
        //INC WORLD MOVEMENT
        incWorldScroll();
        
        //PROCESS FRAME LEVEL. CHECK IF END
        BYTE END_LEVEL = stepLevel();
        
        //MOVE PLAYER
        BOOM = processPlayer(getWorldScroll());
        END  = END_LEVEL || BOOM;
    }
    //}
    
}