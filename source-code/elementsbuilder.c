#include "elementsbuilder.h"
#include "global.h"
#include "world.h"
#include "collisions.h"
#include "captions.h"
#include "sound.h"
#include <stdio.h>
#include <gb/gb.h>
#include <gb/emu_debug.h>

#pragma bank 7

#define LISTSTOPSSIZE 3

ElementType elements[NUMELEMENTS];
unsigned char *background_map_2;
LevelType *elements_map;

//current stop
static UINT8 currentStopFrame = 0;
//current enemy frame x stop
static UINT8 currentEnemyFrame = 0;
//time between shoot
static UINT8 timeBetweenShoot = 0;
//flag clash player
static BYTE clash = FALSE;
//flag frame
static INT8 intermitentFrame = 0;

//LOAD ELEMENT FOR LEVEL
void loadElementsForLevel(int level) BANKED {
    
    currentStopFrame = 0;
    currentEnemyFrame = 0;
    timeBetweenShoot = 0;
    intermitentFrame = 0;
    clash = FALSE;
    
    background_map_2 = getLevelFromIndex(level);
    setCollBoundaries(level);
    //set elements map
    elements_map = buildLevelEnemiesFromIndex(level);
    //num stops
    //EMU_printf("NUM stops %d", elements_map -> numstops);
    //processEnemiesLevel();
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
void createEnemyElement(int index, int pos_x_enemy, int pos_y_enemy, int stop,  int enemy, int type_enemy, int index_id, int frame_id) BANKED {

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
   if (elements[index].type == TYPE_ENEMY_PLANET) {

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

   } else if (elements[index].type == TYPE_ENEMY_STAR) {

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

   } else if (elements[index].type == TYPE_ENEMY_OVNI) {

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

   } else if (elements[index].type == TYPE_ENEMY_SQUARE) {

        elements[index].current_frame = frame_id;       //index frame
        elements[index].num_frames = NUM_FRAMES_PLAYER; //num max frames.

        elements[index].numFrames[0].spritids[0] = 76;
        elements[index].numFrames[0].spritids[1] = 77;
        elements[index].numFrames[0].spritids[2] = 78;
        elements[index].numFrames[0].spritids[3] = 79;
        elements[index].numFrames[0].num_spritids = NUM_IMAGES_BY_FRAME_PLAYER;

        elements[index].numFrames[1].spritids[0] = 80;
        elements[index].numFrames[1].spritids[1] = 81;
        elements[index].numFrames[1].spritids[2] = 82;
        elements[index].numFrames[1].spritids[3] = 83;
        elements[index].numFrames[1].num_spritids = NUM_IMAGES_BY_FRAME_PLAYER;

        elements[index].numFrames[2].spritids[0] = 84;
        elements[index].numFrames[2].spritids[1] = 85;
        elements[index].numFrames[2].spritids[2] = 86;
        elements[index].numFrames[2].spritids[3] = 87;  
        elements[index].numFrames[2].num_spritids = NUM_IMAGES_BY_FRAME_PLAYER;

        elements[index].numFrames[3].spritids[0] = 88;
        elements[index].numFrames[3].spritids[1] = 89;
        elements[index].numFrames[3].spritids[2] = 90;
        elements[index].numFrames[3].spritids[3] = 91;
        elements[index].numFrames[3].num_spritids = NUM_IMAGES_BY_FRAME_PLAYER;

   } 
}

//PROCESS ENEMIES 
//Note: we can charge the data in this way, because there are no so many enemies by level (MAX 19 elements)
//more than 40 this way would be too ineficcient O(n^2)
void processEnemiesLevel(UINT8 stopFrame) BANKED {

    UINT8 index_id = 4;
    UINT8 numElements = 1;

    //for (int i=0; i<elements_map -> numstops; i++) {
        //num groups x stop

    if (stopFrame < elements_map -> numstops) {
        //EMU_printf("STOP %d enemy x group  %d", stopFrame, elements_map->stops[stopFrame].enemiesByStop.num_enemies);

        UINT8 pos_x_enemy = elements_map->stops[stopFrame].enemiesByStop.iniposx;
        UINT8 pos_y_enemy = elements_map->stops[stopFrame].enemiesByStop.iniposy;
        UINT8 frame_id = NO_VALUE;


        for (int j=0; j<elements_map->stops[stopFrame].enemiesByStop.num_enemies; j++) {
  
            //create enemy element and set in elementList 
            createEnemyElement(
                numElements, 
                pos_x_enemy, 
                pos_y_enemy, 
                stopFrame, j,
                elements_map->stops[stopFrame].enemiesByStop.type_enemy,
                index_id, 
                frame_id);

                numElements++;

                pos_x_enemy += ELEMENT_WIDTH;
                index_id = index_id + 4;                                                   //always images of 16x16 so 4 8x8 tiles stored in VRAM
                frame_id++;
                if (frame_id >= elements_map->stops[stopFrame].enemiesByStop.num_frames) { //always there are 4 frames max
                    frame_id = NO_VALUE;
                }                                                    
        }
    }
    //}
}



//MOVE FRAME DISPLACEMENT+ANIMATION
void moveElement(ElementType *element) BANKED {
   
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
void setTilesElement(ElementType *element) BANKED {

   UINT8 frame_idx = element->current_frame;
   UINT8 num_ids = element->numFrames[frame_idx].num_spritids;

   for (int index_sprite = 0; index_sprite < num_ids; index_sprite++) {
       set_sprite_tile(element->current_index+index_sprite, 
                       element->numFrames[frame_idx].spritids[index_sprite]);
   }
}

//MOVE ELEMENT + FRAME + TILE + ANIMATION
void moveTileElement(UINT8 index) BANKED {

    if (elements[index].type != TYPE_EXPLOSION) {
        elements[index].current_frame++;
        if (elements[index].current_frame >= elements[index].num_frames) {
            elements[index].current_frame = 0;
        }
    }
    
    if (elements[index].type == TYPE_PLAYER) {
        if (clash) {
            if (intermitentFrame >= 0) {
                EMU_printf("ACTIVATED intermitence %d",intermitentFrame);
                if (intermitentFrame % 2 == 0) {
                    setTilesElement(&elements[index]);
                } else {
                    deleteTiles(elements[index].current_index);
                }
                intermitentFrame--;
            } else {
                EMU_printf("DEACTIVATE intermitence");
                clash = FALSE;
            }
        } else {
            setTilesElement(&elements[index]);
        }
    } else {
        setTilesElement(&elements[index]);
    }
    moveElement(&elements[index]);
}


//INITIALIZE SHIP
void createPlayer() BANKED {

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
   elements[PLAYER_ID].type_shoot = TYPE_SHOOT_PLAYER_ONE;

   elements[PLAYER_ID].stop_id = NO_STOP;
   elements[PLAYER_ID].enemy_id = NO_GROUP_INDEX;

   elements[PLAYER_ID].current_index = 0;               //set index to VRAM tiles
   elements[PLAYER_ID].current_frame = 0;               //index frame
   elements[PLAYER_ID].num_frames = NUM_FRAMES_PLAYER;  //num max frames.


   if (elements[PLAYER_ID].type == TYPE_PLAYER) {

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
   } 
}

//GET ELEMENT AT INDEX
ElementType *getElement(UINT8 index) BANKED {
    return &elements[index];
}


//PROCESS PLAYER COLLISION AGAINST FOREGROUND (ENEMIES + BULLETS) 
UINT8 collideElementVSOther(ElementType *element, UINT8 currentIndex) BANKED {
    UINT8 index = OVERLIMITELEMENT;    
    BYTE crash = FALSE;
    for(int i=0; i<NUMELEMENTS; i++) {
        if ((elements[i].disabled == FALSE) && (i != currentIndex)) {
            crash = isCollisionB2B(element->x, element->y,
                        element->width, element->height,
                        elements[i].x, elements[i].y,
                        elements[i].width, elements[i].height);

            if (crash) {
                //EMU_printf("COLLISION type %d vs %d type %d",element->type, i, elements[i].type);
                index = i;
                break;
            }
        }
    }
    return index;
} 

//ANIMATE EXPLOSION AND REMOVE ACTIVE ELEMENT.
void processFinalAnimations() BANKED {

    UINT8 deleteData[NUMELEMENTS];
    UINT8 indexDeleteData = 0;
    for (int k=0; k<NUMELEMENTS; k++){deleteData[k]=0;}

    UINT8 moveData[NUMELEMENTS];
    UINT8 indexMoveData = 0;
    for (int j=0; j<NUMELEMENTS; j++){moveData[j]=0;}

    for(int i=0; i<NUMELEMENTS; i++) {
        if (elements[i].disabled == FALSE) {
            if ((elements[i].type == TYPE_EXPLOSION)) {
                elements[i].current_frame = elements[i].current_frame + 1;
                if (elements[i].current_frame >= LIMIT_EXPLOSION) {
                    deleteData[indexDeleteData] = i;
                    indexDeleteData++; 
                } else {
                    moveData[indexMoveData] = i;
                    indexMoveData++;
                }
            
            }
        }
    } 


    for(int a=0; a<indexDeleteData; a++) {
        deleteTiles(elements[deleteData[a]].current_index);
        UINT8 currentIndex = elements[deleteData[a]].current_index;
        deleteContent(&elements[deleteData[a]]);
        elements[deleteData[a]].current_index = currentIndex;
    }

    for (int b=0; b<indexMoveData; b++) {
        moveTileElement(moveData[b]);
    }   

}

//SET EXPLOSION DATA
void setExplosionData(UINT8 index) BANKED {

    elements[index].type = TYPE_EXPLOSION;
    elements[index].current_frame = -1;
    elements[index].num_frames = 2; //num max frames.

    elements[index].x = elements[index].x - TILE_SIZE;

    elements[index].numFrames[0].spritids[0] = 16;
    elements[index].numFrames[0].spritids[1] = 17;
    elements[index].numFrames[0].spritids[2] = 18;
    elements[index].numFrames[0].spritids[3] = 19;
    elements[index].numFrames[0].num_spritids = NUM_IMAGES_BY_FRAME_PLAYER;

    elements[index].numFrames[1].spritids[0] = 20;
    elements[index].numFrames[1].spritids[1] = 21;
    elements[index].numFrames[1].spritids[2] = 22;
    elements[index].numFrames[1].spritids[3] = 23;
    elements[index].numFrames[1].num_spritids = NUM_IMAGES_BY_FRAME_PLAYER;
}


//MOVE BULLETS, DETECT COLLISIONS
void moveBullets(INT16 scroll_x) BANKED {

    UINT8 currentIndex = 0;

    UINT8 deleteData[NUMELEMENTS];
    UINT8 indexDeleteData = 0;
    for (int k=0; k<NUMELEMENTS; k++){deleteData[k]=0;}

    UINT8 moveData[NUMELEMENTS];
    UINT8 indexMoveData = 0;
    for (int j=0; j<NUMELEMENTS; j++){moveData[j]=0;}


    for(int i=1; i<NUMELEMENTS; i++) {
        if (elements[i].disabled == FALSE) {
            if ((elements[i].type == TYPE_SHOOT_PLAYER) || (elements[i].type == TYPE_SHOOT_ENEMY)) {
               
                //IF COLLISION WITH OTHER ELEMENT (ENEMY) -> DESTROY BOTH
                elements[i].x = elements[i].x + elements[i].inc;
                
                UINT8 index = collideElementVSOther(&elements[i], i);

                if (index != OVERLIMITELEMENT) {
                    //destroy bullet
                    //EMU_printf("5)COLLISION bullet %d collision %d type %d", i, index, elements[index].type);

                   

                    if ((index > PLAYER_ID) 
                        && (elements[index].type != TYPE_SHOOT_PLAYER) 
                        && (elements[index].type != TYPE_SHOOT_ENEMY)
                        && (elements[index].type != TYPE_EXPLOSION)) {
                        //destroy enemies/other bullets

                        BYTE found = FALSE;
                        for(int z=0; z<indexDeleteData; z++){
                            if (deleteData[z] == index) {
                                found = TRUE;
                            }
                        }

                        if (!found) { 
                            //ADD ONE TO THE SCORE OF THE PLAYER
                            if (((elements[i].type == TYPE_SHOOT_PLAYER) 
                            && (elements[index].type >= TYPE_ENEMY_PLANET) 
                            && (elements[index].type <= TYPE_ENEMY_SQUARE)) || 
                            ((elements[i].type >= TYPE_ENEMY_PLANET)
                            && (elements[i].type <= TYPE_ENEMY_SQUARE)
                            && (elements[index].type == TYPE_SHOOT_PLAYER))) {
                                elements[PLAYER_ID].scores = elements[PLAYER_ID].scores + 1;
                            }
                            setExplosionData(index);
                        }

                    }  
                    sound_request(SND_EXPLOSION_A);
                    setExplosionData(i);  

                } else {

                    INT16 world_x = elements[i].x + scroll_x; 
                    CollisionData *data = noMoveCollisionShoot(world_x, elements[i].y, elements[i].width, elements[i].type);

                    //COLL AGAINST WORLD
                    if (isCollideElement(data->TILE)) {
                        //collision against other tile of the world
                        //EMU_printf("6)COLLISION bullet %d background %x",i,data->TILE);

                        //play_explosion_type(0);
                        sound_request(SND_EXPLOSION_A);
                        setExplosionData(i);

                    //OUT OF SCREEN
                    } else if ((LIMIT_BOUNDARY_X_INF >= elements[i].x) || (elements[i].x >= LIMIT_BOUNDARY_X_SUP)) {

                        //EMU_printf("7)COLLISION bullet %d out of boundaries %d", i, elements[i].x);
                        //out of screen

                        deleteData[indexDeleteData] = i;
                        indexDeleteData++;


                    } else {
                        //EMU_printf("8)bullet %d moved", i);                        
                        moveData[indexMoveData] = i;
                        indexMoveData++;
                    }
                }
            }
        }
    }//bucle


    for(int a=0; a<indexDeleteData; a++) {
        deleteTiles(elements[deleteData[a]].current_index);
        currentIndex = elements[deleteData[a]].current_index;
        deleteContent(&elements[deleteData[a]]);
        elements[deleteData[a]].current_index = currentIndex;
    }

    for (int b=0; b<indexMoveData; b++) {
        moveTileElement(moveData[b]);
    }
}


//INSERT BULLET INFORMATION INTO ELEMENTS COLLECTION
//index=> index to empty element.
//x => x_position
//y => y_position
//width => (optional) width of the player
//scroll_x => (optional) place of the world
//inc => velocity (+)Player / (-)Enemy
//type => type element
//type_shoot => subkind type element
//frame_id => frame id for explosion.
//index => VRAM memory position 
void createShootInternal(UINT8 index, 
                         UINT16 x, 
                         UINT16 y, 
                         UINT8 width, 
                         INT16 scroll_x, 
                         INT8 inc, 
                         UINT8 type,
                         UINT8 type_shoot, 
                         UINT8 frame_id,
                         UINT8 indexVRAM) BANKED {

   elements[index].disabled = FALSE;

   elements[index].x = x + width;
   elements[index].y = y;
   elements[index].x_world = elements[index].x + scroll_x; 

   elements[index].lives = NO_VALUE;
   elements[index].scores = NO_VALUE;
   elements[index].type = type;
   elements[index].type_shoot = type_shoot;

   elements[index].stop_id = NO_VALUE;
   elements[index].enemy_id = NO_VALUE;
   elements[index].inc = inc;

   elements[index].current_index = indexVRAM;

   elements[index].current_frame = 0;
   elements[index].num_frames = 1;

   if (elements[index].type_shoot  == TYPE_SHOOT_PLAYER_SPECIAL) {
        elements[index].numFrames[0].spritids[0] = 28;
        elements[index].numFrames[0].spritids[1] = 29;
        elements[index].numFrames[0].spritids[2] = 30;
        elements[index].numFrames[0].spritids[3] = 31;
        elements[index].numFrames[0].num_spritids = NUM_IMAGES_BY_FRAME_PLAYER;
     
   } else if ((elements[index].type_shoot  == TYPE_SHOOT_PLAYER_ONE) || (elements[index].type_shoot  == TYPE_SHOOT_PLAYER_TWO) || (elements[index].type_shoot  == TYPE_SHOOT_PLAYER_THREE)) {
        elements[index].numFrames[0].spritids[0] = 24;
        elements[index].numFrames[0].spritids[1] = 25;
        elements[index].numFrames[0].spritids[2] = 26;
        elements[index].numFrames[0].spritids[3] = 27;
        elements[index].numFrames[0].num_spritids = NUM_IMAGES_BY_FRAME_PLAYER;
  
   } 
   //EMU_printf("3)bullet created %d type %d type_shoot %d current_index", elements[index].type, elements[index].type_shoot, elements[index].current_index);
}

//SEARCH FREE ELEMENT SLOT FOR A NEW BULLET (MAX 20 ELEMENTS)
void createShootElement(UINT16 x, UINT16 y, UINT8 width, INT16 scroll_x, INT8 inc, UINT8 type, UINT8 type_shoot) BANKED {
    
    BYTE DONE = FALSE;
    UINT8 index = 0;
    
    for(index=1; index<NUMELEMENTS; index++) {
        if (elements[index].disabled == TRUE) {
            //EMU_printf("2)bucket bullet found in %d", index);
            break;
        }
    }

    if ((index >=1) && (index < NUMELEMENTS)) {
        UINT8 indexVRAM = elements[index].current_index;
        if (indexVRAM == 0) {
            indexVRAM = elements[index-1].current_index + 4;
        }

        if (indexVRAM <= MAXVRAMDEFINITION) {
            //EMU_printf("2)bullet creating in %d, VRAM %d", index, indexVRAM);
            createShootInternal(index, 
                x, 
                y, 
                width, 
                scroll_x, 
                inc, 
                type,
                type_shoot, 
                0,
                indexVRAM);
        } else {
             //EMU_printf("2) Cannot create a bullet max definition %d limit %d",indexVRAM, MAXVRAMDEFINITION);
        }
    }
}

//CREATE SHOOT
void createShoot(INT16 scroll_x) BANKED {

    if (elements[PLAYER_ID].type_shoot == TYPE_SHOOT_PLAYER_ONE) {
        //type normal x 1
        createShootElement(
        elements[PLAYER_ID].x + TILE_SIZE,
        elements[PLAYER_ID].y + 4,
        elements[PLAYER_ID].width,
        scroll_x,
        5,
        TYPE_SHOOT_PLAYER,
        TYPE_SHOOT_PLAYER_ONE 
        );
    } else if (elements[PLAYER_ID].type_shoot == TYPE_SHOOT_PLAYER_TWO) {
        //type normal x 2
        createShootElement(
        elements[PLAYER_ID].x + TILE_SIZE,
        elements[PLAYER_ID].y + 2,
        elements[PLAYER_ID].width,
        scroll_x,
        5,
        TYPE_SHOOT_PLAYER,
        TYPE_SHOOT_PLAYER_TWO
        );

        createShootElement(
        elements[PLAYER_ID].x + TILE_SIZE,
        elements[PLAYER_ID].y + 6,
        elements[PLAYER_ID].width,
        scroll_x,
        5,
        TYPE_SHOOT_PLAYER,
        TYPE_SHOOT_PLAYER_TWO
        );


    } else if (elements[PLAYER_ID].type_shoot == TYPE_SHOOT_PLAYER_THREE) {
        //type normal x 3

        createShootElement(
        elements[PLAYER_ID].x + TILE_SIZE,
        elements[PLAYER_ID].y + 2,
        elements[PLAYER_ID].width,
        scroll_x,
        5,
        TYPE_SHOOT_PLAYER,
        TYPE_SHOOT_PLAYER_THREE
        );

        createShootElement(
        elements[PLAYER_ID].x + TILE_SIZE + TILE_SIZE/2,
        elements[PLAYER_ID].y + 4,
        elements[PLAYER_ID].width,
        scroll_x,
        5,
        TYPE_SHOOT_PLAYER,
        TYPE_SHOOT_PLAYER_THREE
        );

        createShootElement(
        elements[PLAYER_ID].x + TILE_SIZE,
        elements[PLAYER_ID].y + 6,
        elements[PLAYER_ID].width,
        scroll_x,
        5,
        TYPE_SHOOT_PLAYER,
        TYPE_SHOOT_PLAYER_THREE
        );

    } else {
        //type special
        createShootElement(
        elements[PLAYER_ID].x + TILE_SIZE,
        elements[PLAYER_ID].y,
        elements[PLAYER_ID].width,
        scroll_x,
        5,
        TYPE_SHOOT_PLAYER,
        TYPE_SHOOT_PLAYER_SPECIAL 
        );
    }
}


//TIME_SHOOT
void timeCreateShoot(INT16 scroll_x) BANKED {
   if (timeBetweenShoot < 4) {
      //EMU_printf("1)J_A press");
      timeBetweenShoot++;
   } else {
      //EMU_printf("1)J_A create shoot");
      sound_request(SND_LASER_A);
      createShoot(scroll_x); 
      timeBetweenShoot = 0; 
   }  
}


//CLEAN BONUS TILES IN VRAM.
void clear_world_tiles(UINT8 tile_1, UINT8 tile_2, UINT8 tile_3, UINT8 tile_4) BANKED {

    INT8 blank = 240;
    //INT8 blank = 1;
    BYTE DONE = FALSE;
    
    for (int i = 0; (i < 20) && (!DONE); i++) {
        for (int j = 0; (j < 18) && (!DONE) ; j++) {
            UINT8 tile = get_bkg_tile_xy(i,j);
            if ((tile == tile_1)) {
                set_bkg_tiles(i, j, 1, 1, &blank);
                set_bkg_tiles(i, j+1, 1, 1, &blank);
                set_bkg_tiles(i+1, j, 1, 1, &blank);
                set_bkg_tiles(i+1, j+1, 1, 1, &blank);
                sound_request(SND_DING);
                DONE = TRUE;
            }
        }
    }
}

///UINT8 processBonusTilesBackground(UINT8 tile, INT16 tile_x, INT16 tile_y) {

//PROCESS BONUS TILES    
UINT8 processBonusTilesBackground(UINT8 tile) BANKED {
    
    EMU_printf("TILE %x",tile);
    
    if ((tile == TILE_SHOOT_1_1) || (tile == TILE_SHOOT_1_2) || (tile == TILE_SHOOT_1_3) || (tile == TILE_SHOOT_1_4))  {
        elements[PLAYER_ID].type_shoot = TYPE_SHOOT_PLAYER_ONE;
        clear_world_tiles(TILE_SHOOT_1_1, TILE_SHOOT_1_2, TILE_SHOOT_1_3, TILE_SHOOT_1_4);
        return TILE_EMPTY;

    } else if ((tile == TILE_SHOOT_2_1) || (tile == TILE_SHOOT_2_2) || (tile == TILE_SHOOT_2_3) || (tile == TILE_SHOOT_2_4)) {
        elements[PLAYER_ID].type_shoot = TYPE_SHOOT_PLAYER_TWO;
        clear_world_tiles(TILE_SHOOT_2_1, TILE_SHOOT_2_2, TILE_SHOOT_2_3, TILE_SHOOT_2_4);        
        return TILE_EMPTY;

    } else if ((tile == TILE_SHOOT_3_1) || (tile == TILE_SHOOT_3_2) || (tile == TILE_SHOOT_3_3) || (tile == TILE_SHOOT_3_4)) {
        elements[PLAYER_ID].type_shoot = TYPE_SHOOT_PLAYER_THREE;
        clear_world_tiles(TILE_SHOOT_3_1, TILE_SHOOT_3_2, TILE_SHOOT_3_3, TILE_SHOOT_3_4); 
        return TILE_EMPTY;

    }else if ((tile == TILE_SHOOT_S_1) || (tile == TILE_SHOOT_S_2) || (tile == TILE_SHOOT_S_3) || (tile == TILE_SHOOT_S_4)) {
        elements[PLAYER_ID].type_shoot = TYPE_SHOOT_PLAYER_SPECIAL;
        clear_world_tiles(TILE_SHOOT_S_1, TILE_SHOOT_S_2, TILE_SHOOT_S_3, TILE_SHOOT_S_4); 
        return TILE_EMPTY;
    }

    return tile;
}


//PLAYER ACTIONS (MOVEMENTS + SHOOT + COLLISIONS)
UINT8 actionPlayer(INT16 scroll_x) BANKED {

    UINT16 world_x = elements[PLAYER_ID].x + scroll_x;
    UINT16 world_y = elements[PLAYER_ID].y;

    UINT8 dx = 0;
    UINT8 dy = 0;

    UINT8 TILE = TILE_EMPTY;

    if (joypad() & J_LEFT && elements[PLAYER_ID].x > LIMIT_BOUNDARY_X_INF) {
        dx = -elements[PLAYER_ID].inc;
        CollisionData *data = leftCollisionEnv(world_x - elements[PLAYER_ID].inc, world_y);
        //TILE = processBonusTilesBackground(data->TILE, data->x, data->y);
        TILE = processBonusTilesBackground(data->TILE);
        //EMU_printf("LEFT (%d,%d) %hx\n",world_x - elements[PLAYER_ID].inc,world_y,TILE);
    }

    if (joypad() & J_RIGHT && (elements[PLAYER_ID].x + elements[PLAYER_ID].width) < LIMIT_BOUNDARY_X_SUP) {
        dx = elements[PLAYER_ID].inc;
        CollisionData *data = rightCollisionEnv(world_x + dx, world_y, elements[PLAYER_ID].width);
        //TILE = processBonusTilesBackground(data->TILE, data->x, data->y);
        TILE = processBonusTilesBackground(data->TILE);
        //EMU_printf("RIGHT %hx\n",TILE);
    }

    if (joypad() & J_UP && elements[PLAYER_ID].y > LIMIT_BOUNDARY_Y_INF) {
        dy = -elements[PLAYER_ID].inc;
        CollisionData *data = upCollisionEnv(world_x, world_y - elements[PLAYER_ID].inc);
        //TILE = processBonusTilesBackground(data->TILE, data->x, data->y);
        TILE = processBonusTilesBackground(data->TILE);
        //EMU_printf("UP (%d,%d) %hx\n",world_x, world_y - elements[PLAYER_ID].inc,TILE);
    }

    if (joypad() & J_DOWN && (elements[PLAYER_ID].y + elements[PLAYER_ID].height) < LIMIT_BOUNDARY_Y_SUP) {
        dy = elements[PLAYER_ID].inc;
        CollisionData *data = downCollisionEnv(world_x, world_y + dy, elements[PLAYER_ID].height);
        //TILE = processBonusTilesBackground(data->TILE, data->x, data->y);
        TILE = processBonusTilesBackground(data->TILE);
        //EMU_printf("DOWN %hx\n",TILE);
    }

    if (joypad() & J_A) {
        timeCreateShoot(scroll_x);
    }

    if (dx == 0 && dy == 0) {
        CollisionData *data = noMoveCollisionEnv(world_x, world_y, elements[PLAYER_ID].width);
        TILE = processBonusTilesBackground(data->TILE);
        //EMU_printf("NOMOVE %hx\n",TILE);
    }

    elements[PLAYER_ID].x += dx;
    elements[PLAYER_ID].y += dy;

    return TILE;
}

//GO BACK POSITIONS AFTER STAMP AGAINST A WALL.
void rebootPlayer() BANKED  {
    if (!clash) {
        elements[PLAYER_ID].x = elements[PLAYER_ID].x - TILE_SIZE;
        elements[PLAYER_ID].y = elements[PLAYER_ID].y - TILE_SIZE;
        intermitentFrame = 6;
        clash = TRUE;
        //EMU_printf("IntermitentFrame enabled %d", intermitentFrame);
    }
}


//PROCESS PLAYER ACTIONS + COLLISIONS BACKGROUND
BYTE movePlayer(INT16 scroll_x) BANKED {
    UINT8 block = actionPlayer(scroll_x);
    BYTE boom = isCollideElement(block);
    if (!boom) {
        moveTileElement(PLAYER_ID);
    } else {
        
        if (!clash) {
            elements[PLAYER_ID].lives = elements[PLAYER_ID].lives - 1;
        }

        if (elements[PLAYER_ID].lives > 0) {
            rebootPlayer();
            boom = FALSE;
        } else {
            boom = TRUE;
            setExplosionData(PLAYER_ID);
            sound_request(SND_EXPLOSION_A);
            show_game_over_msg();
            wait_frames_level_one(50);
            hide_msg();
        } 
        
    }
    return boom;
}


//COLLIDE EVERYTHING
BYTE collidePlayerVSElements() BANKED {
    BYTE boom = FALSE;
    UINT8 index = collideElementVSOther(&elements[PLAYER_ID], PLAYER_ID);
    if  (index != OVERLIMITELEMENT) {
         if ((elements[index].type != TYPE_SHOOT_PLAYER) && (elements[index].type != TYPE_EXPLOSION)) {
            boom = TRUE;
         }
    }

    if (boom) {
        elements[PLAYER_ID].lives = elements[PLAYER_ID].lives - 1;
        if (elements[PLAYER_ID].lives >= 0) {
            rebootPlayer();
            boom = FALSE;
        } else {
            boom = TRUE;
            setExplosionData(PLAYER_ID);
            show_game_over_msg();
            wait_frames_level_one(50);
            hide_msg(); 
        }
    }
    
    return boom;
}

//CLEAN ELEMENTS 
void deleteContent(ElementType *element) BANKED {

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
void deleteTiles(int index) BANKED {

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
void cleanEnemyDataByStop(UINT8 currentStopFrame) BANKED {

    for(int i=1; i<NUMELEMENTS; i++) {
        //type enemy
        if ((TYPE_ENEMY_PLANET <= elements[i].type) && (elements[i].type <= TYPE_ENEMY_SQUARE)) {
            //current stop
            if (elements[i].stop_id == currentStopFrame) {
                deleteTiles(elements[i].current_index);
                UINT8 current_index = elements[i].current_index;
                deleteContent(&elements[i]);
                elements[i].current_index = current_index;
                //EMU_printf("Delete Enemy element[%d] type enemy %d current_index %d", i, elements[i].type, elements[i].current_index);
            }
        }
    }
}

//PROCESS ENEMIES
void moveEnemies() BANKED {
    
    MovementType *movements = elements_map->stops[currentStopFrame].enemiesByStop.behav_enemy;
    Coordinate *coords;

    //BEGIN INDEX FROM ONE, BECAUSE 0 is PLAYER.
    for(int i=1; i<NUMELEMENTS; i++) {
        //is enabled
        if (elements[i].disabled == FALSE) {
            //is type enemy
            if ((TYPE_ENEMY_PLANET <= elements[i].type) && (elements[i].type <= TYPE_ENEMY_SQUARE)) {
                //current stop
                if (elements[i].stop_id == currentStopFrame) {
                    coords = &movements[currentEnemyFrame].movement[elements[i].enemy_id];
                    elements[i].x += coords->x;
                    elements[i].y += coords->y;
                    moveTileElement(i);
                }
            }
        }
    }
    currentEnemyFrame++;
    if (currentEnemyFrame >= elements_map->stops[currentStopFrame].enemiesByStop.steps) {
        cleanEnemyDataByStop(currentStopFrame);
        elements_map->stops[currentStopFrame].processed = TRUE;
        currentStopFrame = 0;
        currentEnemyFrame = 0;
    }
}



//INITIALIZE_EVERYTHING
void cleanElementData()  BANKED {
   for (int index = 1; index<NUMELEMENTS; index++) {
        deleteContent(&elements[index]);
   }
}

//STOP SCROLLING
BYTE stopScrolling(INT16 scroll_x) BANKED {
    BYTE stopScroll = FALSE;
    
    if (scroll_x < 0) {
        return FALSE;
    }

    UINT8 i = 0;

    while ((i < elements_map->numstops) && (!stopScroll)) {
        if (elements_map->stops[i].processed == FALSE) {
            if (elements_map->stops[i].stop <= scroll_x) {
                stopScroll = TRUE;
                currentStopFrame = i;
                if (elements_map->stops[i].processedEnemies == FALSE) {
                    processEnemiesLevel(currentStopFrame);
                    elements_map->stops[i].processedEnemies = TRUE;
                }
            }
        }
        i++;
    }      
    

    return stopScroll;
}


//DELETE ALL CONTENT OF A LEVEL
void deleteAllContent() BANKED {

    for(int i=1; i<NUMELEMENTS; i++) {
        UINT8 index_number = elements[i].current_index;
        if (index_number != 0) { //index of PLAYER
            deleteTiles(index_number);
        }
        deleteContent(&elements[i]);
    }

}

//DELETE PLAYER
void deletePlayerContent() BANKED {
    deleteTiles(0);
    deleteContent(&elements[0]);
}