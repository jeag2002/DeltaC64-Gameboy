#include <gb/gb.h>
#include <stdio.h>
#include "global.h"
#include "gamebuilder.h"
#include "elementsbuilder.h"
#include "background.h"

#define LEVEL_1_IDX 1
#define STEP 2

void run() {

    //END DUE TO SOMETHING HAPPENED IN THE MAP
    BYTE END_GAME_BG = FALSE;
    //END DUE TO SOMETHING HAPPENED WITH THE ELEMENTS OF THE MAP
    BYTE END_GAME_FG = FALSE;
    //END LEVEL
    BYTE END_LEVEL = FALSE;

    setupPlayer();
    cleanElementData();

    //for(int i = LEVEL_1_IDX; (i<=LEVEL_5_IDX && !END_GAME_BG && !END_GAME_FG); i++) {
    
    //BYTE END_LEVEL = FALSE;   
    fadeout(); 
    launchLevel(LEVEL_1_IDX);
    loadElementsForLevel(LEVEL_1_IDX);
    
    ElementType *player = getElement(PLAYER_ID);

    UINT8 enemy_timer = 0;
    UINT8 bullet_timer = 0;

    fadein();


    while ((!END_GAME_BG) && (!END_GAME_FG) && (!END_LEVEL)){

        wait_vbl_done();
        
        //MOVE PLAYER. CRASH IF SOMETHING HAPPENED WHEN PLAYER INTERACT WITH THE BACKGROUND
        END_GAME_BG = movePlayer(getWorldScroll());

        if (!stopScrolling(getWorldScroll())) {
             //INC WORLD MOVEMENT
            incWorldScroll();
        } else {
            //MOVE ENEMIES, EVERY 3 FRAMES.
            if(++enemy_timer == 3) {
                enemy_timer = 0;
                moveEnemies();  
            }
        }

        //CRASH IF SOMETHING HAPPENED WHEN PLAYER INTERACT WITH THE FOREGROUND
        END_GAME_FG = collideElements();

        //MOVE BULLETS
        if (++bullet_timer == 4) {
            bullet_timer = 0;
            performantDelay(STEP);
            moveBullets(getWorldScroll());
        }

        //PROCESS FRAME LEVEL. CHECK IF END
        END_LEVEL = stepLevel();
        //SET SCORE PLAYER
        setHUD(player->scores, player->type_shoot, player->lives);
    }

    deleteAllContent();
    //}    
    deletePlayerContent();
    clear_bkg_screen();
}