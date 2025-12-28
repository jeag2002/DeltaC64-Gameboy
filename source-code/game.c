#include <gb/gb.h>
#include <stdio.h>
#include "gamebuilder.h"
#include "elementsbuilder.h"
#include "background.h"

#define LEVEL_1_IDX 1
#define STEP 2

void run() {

    BYTE END = FALSE;
    BYTE END_LEVEL = FALSE;


    setupPlayer();

    //for(int i = LEVEL_1_IDX; (i<=LEVEL_5_IDX && !END); i++) {
    //END_LEVEL = FALSE;
    launchLevel(LEVEL_1_IDX);
    loadElementsForLevel(LEVEL_1_IDX);
    
    
    int score = 1;

    ElementType *player = getElement(PLAYER_ID);


    while ((!END) && (!END_LEVEL)){

        //SET SCORE PLAYER
        setHUD(player->scores, player->lives);
        
        //DELAY
        performantDelay(STEP);
        
        //INC WORLD MOVEMENT
        incWorldScroll();
        
        //PROCESS FRAME LEVEL. CHECK IF END
        END_LEVEL = stepLevel();
        
        //MOVE PLAYER
        END = processPlayer(getWorldScroll());
    }
    //}
    
}