#include "elementsbuilder.h"
#include "global.h"
#include "world.h"
#include "collisions.h"
#include <stdio.h>
#include <gb/gb.h>
#include <gb/emu_debug.h>

#define LISTSTOPSSIZE 3

ElementType elements[NUMELEMENTS];
unsigned char *background_map_2;
LevelType *elements_map;

//elements ini index for elementType.
static UINT8 currentElements = 1;
//current stop
static UINT8 currentStopFrame = 0;
//current enemy frame x stop
static UINT8 currentEnemyFrame = 0;

//LOAD ELEMENT FOR LEVEL
void loadElementsForLevel(int level) {
    background_map_2 = getLevelFromIndex(level);
    setCollBoundaries(level);
    //set elements map
    elements_map = buildLevelEnemiesFromIndex(level);
    processEnemiesLevel();
}

//SET ENEMY in elements collection.
//index => element index into Elements collection
//pos_x_enemy => pos x enemy in the screen
//pos_y_enemy => pos y enemy in the screen
//stop => stop level
//group => group level
//enemy => enemy level
//type_enemy => kind of enemy
//index_id => first VRAM index
//frame_id => first frame.
void createEnemyElement(int index, int pos_x_enemy, int pos_y_enemy, int stop,  int enemy, int type_enemy, int index_id, int frame_id) {

   elements[index].disabled = FALSE;

   elements[index].x = pos_x_enemy;
   elements[index].y = pos_y_enemy;
   elements[index].x_world = NO_VALUE; 

   elements[index].width = ELEMENT_WIDTH;
   elements[index].height = ELEMENT_HEIGHT;
   elements[index].inc = NO_VALUE; //the movement is done externaly

   elements[index].lives = NO_VALUE; //enemy will disapear at first crash
   elements[index].scores = NO_VALUE;

   elements[index].type = type_enemy; //type enemy
   elements[index].type_shoot = NO_SHOOT;

   //where the enemy is situated
   elements[index].stop_id = stop;
   elements[index].enemy_id = enemy;
   
   //VRAM tiles
   elements[index].current_index = index_id;

   //SET FRAMES.
   if (type_enemy == TYPE_ENEMY_PLANET) {

        elements[index].current_frame = frame_id;       //index frame
        elements[index].num_frames = NUM_FRAMES_PLAYER; //num max frames.

        elements[index].numFrames[0].spritids[0] = 60;
        elements[index].numFrames[0].spritids[1] = 61;
        elements[index].numFrames[0].spritids[2] = 62;
        elements[index].numFrames[0].spritids[3] = 63;
        elements[index].numFrames[0].num_spritids = NUM_IMAGES_BY_FRAME_PLAYER;

        elements[index].numFrames[1].spritids[0] = 64;
        elements[index].numFrames[1].spritids[1] = 65;
        elements[index].numFrames[1].spritids[2] = 66;
        elements[index].numFrames[1].spritids[3] = 67;
        elements[index].numFrames[1].num_spritids = NUM_IMAGES_BY_FRAME_PLAYER;

        elements[index].numFrames[2].spritids[0] = 68;
        elements[index].numFrames[2].spritids[1] = 69;
        elements[index].numFrames[2].spritids[2] = 70;
        elements[index].numFrames[2].spritids[3] = 71;  
        elements[index].numFrames[2].num_spritids = NUM_IMAGES_BY_FRAME_PLAYER;

        elements[index].numFrames[3].spritids[0] = 72;
        elements[index].numFrames[3].spritids[1] = 73;
        elements[index].numFrames[3].spritids[2] = 74;
        elements[index].numFrames[3].spritids[3] = 75;
        elements[index].numFrames[3].num_spritids = NUM_IMAGES_BY_FRAME_PLAYER;

   } else if (type_enemy == TYPE_ENEMY_STAR) {

        elements[index].current_frame = frame_id; //index frame
        elements[index].num_frames = 2;    //num max frames.

        elements[index].numFrames[0].spritids[0] = 52;
        elements[index].numFrames[0].spritids[1] = 53;
        elements[index].numFrames[0].spritids[2] = 54;
        elements[index].numFrames[0].spritids[3] = 55;
        elements[index].numFrames[0].num_spritids = NUM_IMAGES_BY_FRAME_PLAYER;

        elements[index].numFrames[1].spritids[0] = 56;
        elements[index].numFrames[1].spritids[1] = 57;
        elements[index].numFrames[1].spritids[2] = 58;
        elements[index].numFrames[1].spritids[3] = 59;
        elements[index].numFrames[1].num_spritids = NUM_IMAGES_BY_FRAME_PLAYER;

   } else if (type_enemy == TYPE_ENEMY_OVNI) {

        elements[index].current_frame = frame_id;       //index frame
        elements[index].num_frames = NUM_FRAMES_PLAYER; //num max frames.

        elements[index].numFrames[0].spritids[0] = 36;
        elements[index].numFrames[0].spritids[1] = 37;
        elements[index].numFrames[0].spritids[2] = 38;
        elements[index].numFrames[0].spritids[3] = 39;
        elements[index].numFrames[0].num_spritids = NUM_IMAGES_BY_FRAME_PLAYER;

        elements[index].numFrames[1].spritids[0] = 40;
        elements[index].numFrames[1].spritids[1] = 41;
        elements[index].numFrames[1].spritids[2] = 42;
        elements[index].numFrames[1].spritids[3] = 43;
        elements[index].numFrames[1].num_spritids = NUM_IMAGES_BY_FRAME_PLAYER;

        elements[index].numFrames[2].spritids[0] = 44;
        elements[index].numFrames[2].spritids[1] = 45;
        elements[index].numFrames[2].spritids[2] = 46;
        elements[index].numFrames[2].spritids[3] = 47;  
        elements[index].numFrames[2].num_spritids = NUM_IMAGES_BY_FRAME_PLAYER;

        elements[index].numFrames[3].spritids[0] = 48;
        elements[index].numFrames[3].spritids[1] = 49;
        elements[index].numFrames[3].spritids[2] = 50;
        elements[index].numFrames[3].spritids[3] = 51;
        elements[index].numFrames[3].num_spritids = NUM_IMAGES_BY_FRAME_PLAYER;
   }
}

//PROCESS ENEMIES 
//Note: we can charge the data in this way, because there are no so many enemies by level (MAX 19 elements)
//more than 40 this way would be too ineficcient O(n^2)
void processEnemiesLevel() {

    UINT8 index_id = 4;

    //num stops
    EMU_printf("NUM stops %d", elements_map -> numstops);

    for (int i=0; i<elements_map -> numstops; i++) {
        //num groups x stop

        EMU_printf("NUM enemy x group  %d", elements_map->stops[i].enemiesByStop.num_enemies);

        UINT8 pos_x_enemy = ENEMY_POS_X_INI;
        UINT8 pos_y_enemy = ENEMY_POS_Y_INI;
        UINT8 frame_id = NO_VALUE;


        for (int j=0; j<elements_map->stops[i].enemiesByStop.num_enemies; j++) {
  
            //create enemy element and set in elementList 
            createEnemyElement(
                currentElements, 
                pos_x_enemy, 
                pos_y_enemy, 
                i, j,
                elements_map->stops[i].enemiesByStop.type_enemy,
                index_id, 
                frame_id);

                pos_x_enemy += ELEMENT_WIDTH;
                index_id = index_id + 4;                                            //always images of 16x16 so 4 8x8 tiles stored in VRAM
                frame_id++;
                
                if (frame_id >= elements_map->stops[i].enemiesByStop.num_frames) {  //always there are 4 frames max
                    frame_id = NO_VALUE;
                } 
                currentElements++;                                                  //max 20 elements in the scenario                                                        
        }
    }
}



//MOVE FRAME DISPLACEMENT+ANIMATION
void moveElement(ElementType *element) {
   
   UINT8 frame_idx = element->current_frame;
   UINT8 num_ids = element->numFrames[frame_idx].num_spritids;

   for (int index_sprite = 0; index_sprite < num_ids; index_sprite++) {

      UINT8 _x = element->x;
      UINT8 _y = element->y;

      if (index_sprite == 1) {
         _x = _x + TILE_SIZE;
      } else if (index_sprite == 2) {
         _y = _y + TILE_SIZE;
      } else if (index_sprite == 3) {
         _x = _x + TILE_SIZE;
         _y = _y + TILE_SIZE;
      }

      move_sprite(element->current_index+index_sprite, _x, _y);
   }
}


//CHANGE SPRITE ANIMATION IN VRAM
void setTilesElement(ElementType *element) {

   UINT8 frame_idx = element->current_frame;
   UINT8 num_ids = element->numFrames[frame_idx].num_spritids;

   for (int index_sprite = 0; index_sprite < num_ids; index_sprite++) {
       set_sprite_tile(element->current_index+index_sprite, 
                       element->numFrames[frame_idx].spritids[index_sprite]);
   }
}


//MOVE ELEMENT + FRAME + TILE + ANIMATION
void moveTileElement(UINT8 index) {
    elements[index].current_frame++;
    if (elements[index].current_frame >= elements[index].num_frames) {
       elements[index].current_frame = 0;
    }

    setTilesElement(&elements[index]);
    moveElement(&elements[index]);
}


//INITIALIZE SHIP
void setupPlayer() {

   elements[PLAYER_ID].disabled = FALSE;

   elements[PLAYER_ID].x = PLAYER_POS_X_INI;
   elements[PLAYER_ID].y = PLAYER_POS_Y_INI;
   elements[PLAYER_ID].x_world = elements[PLAYER_ID].x; 

   elements[PLAYER_ID].width = ELEMENT_WIDTH;
   elements[PLAYER_ID].height = ELEMENT_HEIGHT;
   elements[PLAYER_ID].inc = INC_PLAYER;

   elements[PLAYER_ID].lives = LIVES_PLAYER;
   elements[PLAYER_ID].scores = SCORE_PLAYER;

   elements[PLAYER_ID].type = TYPE_PLAYER;
   
   elements[PLAYER_ID].type_shoot = NO_SHOOT;

   elements[PLAYER_ID].stop_id = NO_STOP;
   elements[PLAYER_ID].enemy_id = NO_GROUP_INDEX;

   elements[PLAYER_ID].current_index = 0;               //set index to VRAM tiles
   elements[PLAYER_ID].current_frame = 0;               //index frame
   elements[PLAYER_ID].num_frames = NUM_FRAMES_PLAYER;  //num max frames.

   elements[PLAYER_ID].numFrames[0].spritids[0] = 0;
   elements[PLAYER_ID].numFrames[0].spritids[1] = 1;
   elements[PLAYER_ID].numFrames[0].spritids[2] = 2;
   elements[PLAYER_ID].numFrames[0].spritids[3] = 3;
   elements[PLAYER_ID].numFrames[0].num_spritids = NUM_IMAGES_BY_FRAME_PLAYER;

   elements[PLAYER_ID].numFrames[1].spritids[0] = 4;
   elements[PLAYER_ID].numFrames[1].spritids[1] = 5;
   elements[PLAYER_ID].numFrames[1].spritids[2] = 6;
   elements[PLAYER_ID].numFrames[1].spritids[3] = 7;
   elements[PLAYER_ID].numFrames[1].num_spritids = NUM_IMAGES_BY_FRAME_PLAYER;

   elements[PLAYER_ID].numFrames[2].spritids[0] = 8;
   elements[PLAYER_ID].numFrames[2].spritids[1] = 9;
   elements[PLAYER_ID].numFrames[2].spritids[2] = 10;
   elements[PLAYER_ID].numFrames[2].spritids[3] = 11;  
   elements[PLAYER_ID].numFrames[2].num_spritids = NUM_IMAGES_BY_FRAME_PLAYER;

   elements[PLAYER_ID].numFrames[3].spritids[0] = 12;
   elements[PLAYER_ID].numFrames[3].spritids[1] = 13;
   elements[PLAYER_ID].numFrames[3].spritids[2] = 14;
   elements[PLAYER_ID].numFrames[3].spritids[3] = 15;
   elements[PLAYER_ID].numFrames[3].num_spritids = NUM_IMAGES_BY_FRAME_PLAYER;
     
   setTilesElement(&elements[PLAYER_ID]);
   moveElement(&elements[PLAYER_ID]);
}

//GET ELEMENT AT INDEX
ElementType *getElement(UINT8 index) {
    return &elements[index];
}

/**
 * Player Movement strategy
 * 
 * @param scroll_x 
 * @return BYTE 
 */

UINT8 actionPlayer(INT16 scroll_x) {

    UINT16 world_x = elements[PLAYER_ID].x + scroll_x;
    UINT16 world_y = elements[PLAYER_ID].y;

    UINT8 dx = 0;
    UINT8 dy = 0;

    UINT8 TILE = TILE_EMPTY;

    if (joypad() & J_LEFT && elements[PLAYER_ID].x > LIMIT_BOUNDARY_X_INF) {
        dx = -elements[PLAYER_ID].inc;
        TILE = leftCollisionEnv(world_x - elements[PLAYER_ID].inc, world_y);
        //EMU_printf("LEFT (%d,%d) %hx\n",world_x - elements[PLAYER_ID].inc,world_y,TILE);
    }

    if (joypad() & J_RIGHT && (elements[PLAYER_ID].x + elements[PLAYER_ID].width) < LIMIT_BOUNDARY_X_SUP) {
        dx = elements[PLAYER_ID].inc;
        TILE = rightCollisionEnv(world_x + dx, world_y, elements[PLAYER_ID].width);
        //EMU_printf("RIGHT %hx\n",TILE);
    }

    if (joypad() & J_UP && elements[PLAYER_ID].y > LIMIT_BOUNDARY_Y_INF) {
        dy = -elements[PLAYER_ID].inc;
        TILE = upCollisionEnv(world_x, world_y - elements[PLAYER_ID].inc);
        //EMU_printf("UP (%d,%d) %hx\n",world_x, world_y - elements[PLAYER_ID].inc,TILE);
    }

    if (joypad() & J_DOWN && (elements[PLAYER_ID].y + elements[PLAYER_ID].height) < LIMIT_BOUNDARY_Y_SUP) {
        dy = elements[PLAYER_ID].inc;
        TILE = downCollisionEnv(world_x, world_y + dy, elements[PLAYER_ID].height);
        //EMU_printf("DOWN %hx\n",TILE);
    }

    if (dx == 0 && dy == 0) {
        TILE = noMoveCollisionEnv(world_x, world_y, elements[PLAYER_ID].width);
        //EMU_printf("NOMOVE %hx\n",TILE);
    }

    elements[PLAYER_ID].x += dx;
    elements[PLAYER_ID].y += dy;

    return TILE;
}

//PROCESS PLAYER
BYTE movePlayer(INT16 scroll_x) {
    UINT8 block = actionPlayer(scroll_x);
    BYTE boom = isCollideElement(block);
    if (!boom) {
        moveTileElement(PLAYER_ID);
    }
    return boom;
}


//PLAYER vs 
UINT8 collidePlayerVSOther() {
    UINT8 index = 0;
    BYTE crash = FALSE;
    for(int i=1; ((i<currentElements) && (!crash)); i++) {

        crash = isCollisionB2B(elements[PLAYER_ID].x, elements[PLAYER_ID].y,
                     elements[PLAYER_ID].width, elements[PLAYER_ID].height,
                     elements[i].x, elements[i].y,
                     elements[i].width, elements[i].height);

        if (crash) {
            index = i;
        }
    }
    return index;
} 


//COLLIDE EVERYTHING
BYTE collideElements() {
    BYTE boom = FALSE;
    UINT8 index = collidePlayerVSOther();
    boom = (index > PLAYER_ID);
    return boom;
}

//CLEAN ELEMENTS 
void deleteContent(ElementType *element) {

    element->disabled = TRUE;  
    element->x = 0;
    element->y = 0;
    element->x_world = 0;
    element->width = 0;
    element->height = 0;  
    element->inc = 0;
    element->lives = 0;
    element->scores = 0;

    element->current_index = 0; //index image
    element->current_frame = 0; //index frame
    element->num_frames = 0;    //num max frames.

    element->type = 0;
    element->type_shoot = 0;
    element->stop_id = 0;
    element->enemy_id = 0;

    for (int index_frame = 0; index_frame < FRAMES; index_frame++) {
        element->numFrames[index_frame].spritids[0] = 32;
        element->numFrames[index_frame].spritids[1] = 33;
        element->numFrames[index_frame].spritids[2] = 34;
        element->numFrames[index_frame].spritids[3] = 35;
        element->numFrames[index_frame].num_spritids = 0;
    }
}

//CLEAN DATA OF VRAM
void deleteTiles(int index) {

   move_sprite(index, 0, 0);
   move_sprite(index+1, 0, 0);
   move_sprite(index+2, 0, 0);
   move_sprite(index+3, 0, 0);

   set_sprite_tile(index, 33);
   set_sprite_tile(index+1, 34);
   set_sprite_tile(index+2, 35);
   set_sprite_tile(index+3, 36);
}

//CLEAN ELEMENTS x STOP
void cleanEnemyDataByStop(UINT8 currentStopFrame) {

    for(int i=1; i<currentElements; i++) {
        //type enemy
        if ((TYPE_ENEMY_PLANET <= elements[i].type) && (elements[i].type <= TYPE_ENEMY_OVNI)) {
            //current stop
            if (elements[i].stop_id == currentStopFrame) {
                deleteTiles(elements[i].current_index);
                deleteContent(&elements[i]);
            }
        }
    }
}

//PROCESS ENEMIES
void moveEnemies() {
    
    MovementType *movements = elements_map->stops[currentStopFrame].enemiesByStop.behav_enemy;
    Coordinate *coords;

    //BEGIN INDEX FROM ONE, BECAUSE 0 is PLAYER.
    for(int i=1; i<currentElements; i++) {
        //is enabled
        if (elements[i].disabled == FALSE) {
            //is type enemy
            if ((TYPE_ENEMY_PLANET <= elements[i].type) && (elements[i].type <= TYPE_ENEMY_OVNI)) {
                //current stop
                if (elements[i].stop_id == currentStopFrame) {
                    coords = &movements[currentEnemyFrame].movement[elements[i].enemy_id];
                    EMU_printf("stop %d, frame %d, enemy %d coord (%d,%d)", currentStopFrame, currentEnemyFrame, elements[i].enemy_id, coords->x, coords->y);
                    elements[i].x += coords->x;
                    elements[i].y += coords->y;
                    moveTileElement(i);
                }
            }
        }
    }
    currentEnemyFrame++;
    if (currentEnemyFrame >= NUMSTEPS) {
        cleanEnemyDataByStop(currentStopFrame);
        elements_map->stops[currentStopFrame].processed = TRUE;
        currentStopFrame = 0;
        currentEnemyFrame = 0;
    }
}



//INITIALIZE_EVERYTHING
void cleanElementData()  {
   for (int index = 1; index<NUMELEMENTS; index++) {
        deleteContent(&elements[index]);
   }
}

//STOP SCROLLING
BYTE stopScrolling(INT16 scroll_x) {
    BYTE stopScroll = FALSE;

    if (scroll_x < 0) {
        return FALSE;
    }

    UINT8 i = 0;

    while ((i < elements_map->numstops) && (!stopScroll)) {
        if (elements_map->stops[i].processed == FALSE) {
            //EMU_printf("stop %d scroll_x %d", elements_map->stops[i].stop, scroll_x);
            if (elements_map->stops[i].stop <= scroll_x) {
                stopScroll = TRUE;
                currentStopFrame = i;
            }
        }
        i++;
    }      
    

    return stopScroll;
}