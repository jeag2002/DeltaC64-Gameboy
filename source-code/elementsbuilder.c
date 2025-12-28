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
UINT8 numElements = 1;

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
void createEnemyElement(int index, int pos_x_enemy, int pos_y_enemy, int stop, int group, int enemy, int type_enemy, int index_id, int frame_id) {

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
   elements[index].group_id = group;
   elements[index].group_id_index = enemy;
   
   //VRAM tiles
   elements[index].current_index = index_id;

   //SET FRAMES.
   if (type_enemy == TYPE_ENEMY_PLANET) {

        elements[index].current_frame = frame_id;       //index frame
        elements[index].num_frames = NUM_FRAMES_PLAYER; //num max frames.

        elements[index].numFrames[0].spritids[0] = 61;
        elements[index].numFrames[0].spritids[1] = 62;
        elements[index].numFrames[0].spritids[2] = 63;
        elements[index].numFrames[0].spritids[3] = 64;
        elements[index].numFrames[0].num_spritids = NUM_IMAGES_BY_FRAME_PLAYER;

        elements[index].numFrames[1].spritids[0] = 65;
        elements[index].numFrames[1].spritids[1] = 66;
        elements[index].numFrames[1].spritids[2] = 67;
        elements[index].numFrames[1].spritids[3] = 68;
        elements[index].numFrames[1].num_spritids = NUM_IMAGES_BY_FRAME_PLAYER;

        elements[index].numFrames[2].spritids[0] = 69;
        elements[index].numFrames[2].spritids[1] = 70;
        elements[index].numFrames[2].spritids[2] = 71;
        elements[index].numFrames[2].spritids[3] = 72;  
        elements[index].numFrames[2].num_spritids = NUM_IMAGES_BY_FRAME_PLAYER;

        elements[index].numFrames[3].spritids[0] = 73;
        elements[index].numFrames[3].spritids[1] = 74;
        elements[index].numFrames[3].spritids[2] = 75;
        elements[index].numFrames[3].spritids[3] = 76;
        elements[index].numFrames[3].num_spritids = NUM_IMAGES_BY_FRAME_PLAYER;

   } else if (type_enemy == TYPE_ENEMY_STAR) {

        elements[index].current_frame = frame_id; //index frame
        elements[index].num_frames = 2;    //num max frames.

        elements[index].numFrames[0].spritids[0] = 53;
        elements[index].numFrames[0].spritids[1] = 54;
        elements[index].numFrames[0].spritids[2] = 55;
        elements[index].numFrames[0].spritids[3] = 56;
        elements[index].numFrames[0].num_spritids = NUM_IMAGES_BY_FRAME_PLAYER;

        elements[index].numFrames[1].spritids[0] = 57;
        elements[index].numFrames[1].spritids[1] = 58;
        elements[index].numFrames[1].spritids[2] = 59;
        elements[index].numFrames[1].spritids[3] = 60;
        elements[index].numFrames[1].num_spritids = NUM_IMAGES_BY_FRAME_PLAYER;

   } else if (type_enemy == TYPE_ENEMY_OVNI) {

        elements[index].current_frame = frame_id;       //index frame
        elements[index].num_frames = NUM_FRAMES_PLAYER; //num max frames.

        elements[index].numFrames[0].spritids[0] = 37;
        elements[index].numFrames[0].spritids[1] = 38;
        elements[index].numFrames[0].spritids[2] = 39;
        elements[index].numFrames[0].spritids[3] = 40;
        elements[index].numFrames[0].num_spritids = NUM_IMAGES_BY_FRAME_PLAYER;

        elements[index].numFrames[1].spritids[0] = 41;
        elements[index].numFrames[1].spritids[1] = 42;
        elements[index].numFrames[1].spritids[2] = 43;
        elements[index].numFrames[1].spritids[3] = 44;
        elements[index].numFrames[1].num_spritids = NUM_IMAGES_BY_FRAME_PLAYER;

        elements[index].numFrames[2].spritids[0] = 45;
        elements[index].numFrames[2].spritids[1] = 46;
        elements[index].numFrames[2].spritids[2] = 47;
        elements[index].numFrames[2].spritids[3] = 48;  
        elements[index].numFrames[2].num_spritids = NUM_IMAGES_BY_FRAME_PLAYER;

        elements[index].numFrames[3].spritids[0] = 49;
        elements[index].numFrames[3].spritids[1] = 50;
        elements[index].numFrames[3].spritids[2] = 51;
        elements[index].numFrames[3].spritids[3] = 52;
        elements[index].numFrames[3].num_spritids = NUM_IMAGES_BY_FRAME_PLAYER;
   }
}

//PROCESS ENEMIES 
//Note: we can charge the data in this way, because there is no so many enemies x level (MAX 19 elements)
//more than 20-40 this way would be too ineficcient O(n^3)
void processEnemiesLevel() {

    UINT8 index_id = 4;

    //num stops
    EMU_printf("NUM stops %d", elements_map -> numstops);

    for (int i=0; i<elements_map -> numstops; i++) {
        //num groups x stop
        EMU_printf("NUM group x stop  %d", elements_map->stops[i].groupEnemiesByStop);
        for (int j=0; j<elements_map->stops[i].groupEnemiesByStop; j++) {
  
            UINT8 pos_x_enemy = ENEMY_POS_X_INI;
            UINT8 pos_y_enemy = ENEMY_POS_Y_INI;
            UINT8 frame_id = NO_VALUE;

            //num enemies x group
            for (int k=0; k<elements_map->stops[i].enemiesByStop[j].num_enemies; k++) {

                EMU_printf("NUM enemy x group  %d", elements_map->stops[i].enemiesByStop[j].num_enemies);

                //create enemy element and set in elementList 
                createEnemyElement(
                numElements, 
                pos_x_enemy, 
                pos_y_enemy, 
                i, j, k, 
                elements_map->stops[i].enemiesByStop[j].type_enemy,
                index_id, 
                frame_id);

                pos_x_enemy += ELEMENT_WIDTH;
                index_id = index_id + 4;                                                        //always there are 4 tiles
                frame_id = (frame_id + 1) % elements_map->stops[i].enemiesByStop[j].num_frames; //always there are 4 frames max
                numElements++;                                                                  //max 20 elements in the scenario                                                        
            }

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
   elements[PLAYER_ID].group_id = NO_GROUP;
   elements[PLAYER_ID].group_id_index = NO_GROUP_INDEX;

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

UINT8 actionPlayer(UINT16 scroll_x) {

    UINT16 world_x = elements[PLAYER_ID].x + scroll_x;
    UINT16 world_y = elements[PLAYER_ID].y;

    UINT8 dx = 0;
    UINT8 dy = 0;

    UINT8 TILE = TILE_EMPTY;

    if (joypad() & J_LEFT && elements[PLAYER_ID].x > LIMIT_BOUNDARY_X_INF) {
        dx = -elements[PLAYER_ID].inc;
        TILE = leftCollisionEnv(world_x - elements[PLAYER_ID].inc, world_y);
        EMU_printf("LEFT (%d,%d) %hx\n",world_x - elements[PLAYER_ID].inc,world_y,TILE);
    }

    if (joypad() & J_RIGHT && (elements[PLAYER_ID].x + elements[PLAYER_ID].width) < LIMIT_BOUNDARY_X_SUP) {
        dx = elements[PLAYER_ID].inc;
        TILE = rightCollisionEnv(world_x + dx, world_y, elements[PLAYER_ID].width);
        EMU_printf("RIGHT %hx\n",TILE);
    }

    if (joypad() & J_UP && elements[PLAYER_ID].y > LIMIT_BOUNDARY_Y_INF) {
        dy = -elements[PLAYER_ID].inc;
        TILE = upCollisionEnv(world_x, world_y - elements[PLAYER_ID].inc);
        EMU_printf("UP (%d,%d) %hx\n",world_x, world_y - elements[PLAYER_ID].inc,TILE);
    }

    if (joypad() & J_DOWN && (elements[PLAYER_ID].y + elements[PLAYER_ID].height) < LIMIT_BOUNDARY_Y_SUP) {
        dy = elements[PLAYER_ID].inc;
        TILE = downCollisionEnv(world_x, world_y + dy, elements[PLAYER_ID].height);
        EMU_printf("DOWN %hx\n",TILE);
    }

    if (dx == 0 && dy == 0) {
        TILE = noMoveCollisionEnv(world_x, world_y, elements[PLAYER_ID].width);
        EMU_printf("NOMOVE %hx\n",TILE);
    }

    elements[PLAYER_ID].x += dx;
    elements[PLAYER_ID].y += dy;

    return TILE;
}


BYTE processPlayer(UINT16 scroll_x) {
    UINT8 block = actionPlayer(scroll_x);
    BYTE boom = isCollideElement(block);
    if (!boom) {
        moveTileElement(PLAYER_ID);
    }
    return boom;
}



//OLD CODE.

/*
UBYTE isCollision(UINT16 elem_1_x, UINT16 elem_1_y, UINT16 wall_x, UINT16 wall_y) {
    return (elem_1_x >= wall_x && elem_1_x <= wall_x + 16) 
    && (elem_1_y >= wall_y && elem_1_y <= wall_y +  16) 
    || (wall_x >= elem_1_x && wall_x <= elem_1_x +  16) 
    && (wall_y >= elem_1_y && wall_y <= elem_1_y +  16);
}



BYTE is_wall(UINT8 tile) {
    if(tile == 0xFF) return TRUE;   // fuera = sólido
    return (tile != 0x7A);         
}


UINT8 get_tile_at_world(UINT16 world_x, UINT16 world_y) {

    //INT16 wx = (world_x / TILE) -1;
    //INT16 wy = (world_y / TILE) -2;

    INT16 wx = (world_x / TILE_SIZE);
    INT16 wy = (world_y / TILE_SIZE);

    if (wx < 1 || wy < 2 || wx >= 200 || wy >= 18) {
        return 0xFF;
    }

    return background_map_2[wy * MAP_WIDTH_TILE + wx];
    //return background_map_levelone[wy * MAP_WIDTH_TILE + wx];
}

BYTE down_collision(UINT16 world_x, UINT16 world_y) {

    return FALSE;
    
    UINT16 y = world_y + 15;   // borde inferior del sprite
    UINT16 x1 = world_x - 7;   // borde izquierdo
    UINT16 x2 = world_x;       // centro
    UINT16 x3 = world_x + 7;   // borde derecho

    UINT8 tiles_1 = get_tile_at_world(x1, y);
    UINT8 tiles_2 = get_tile_at_world(x2, y);
    UINT8 tiles_3 = get_tile_at_world(x3, y);

    if ((tiles_2 != 0x7A) && (tiles_2 != 0xFF)) {
       return TRUE;
    }
    
    
    if ((tiles_1 != 0x7A) && (tiles_1 != 0xFF)) {
       return TRUE;
    }

    if ((tiles_3 != 0x7A) && (tiles_3 != 0xFF)) {
        return TRUE;
    }
    

    return FALSE;
}



BYTE up_collision(UINT16 world_x, UINT16 world_y) {

    return FALSE;

    UINT16 y = world_y - 1;    // borde superior
    UINT16 x1 = world_x - 7;
    UINT16 x2 = world_x;
    UINT16 x3 = world_x + 7;

    UINT8 tiles_1 = get_tile_at_world(x1, y);
    UINT8 tiles_2 = get_tile_at_world(x2, y);
    UINT8 tiles_3 = get_tile_at_world(x3, y);

    if ((tiles_2 != 0x7A) && (tiles_2 != 0xFF)) {
       return TRUE;
    }
    
    if ((tiles_1 != 0x7A) && (tiles_1 != 0xFF)) {
       return TRUE;
    }

    if ((tiles_3 != 0x7A) && (tiles_3 != 0xFF)) {
        return TRUE;
    }
    
    return FALSE;
}



BYTE left_collision(UINT16 world_x, UINT16 world_y) {

    return FALSE;

    UINT16 x  = world_x - 1;    // borde izquierdo
    UINT16 y1 = world_y - 7;
    UINT16 y2 = world_y;
    UINT16 y3 = world_y + 7;


    UINT8 tiles_1 = get_tile_at_world(x, y1);
    UINT8 tiles_2 = get_tile_at_world(x, y2);
    UINT8 tiles_3 = get_tile_at_world(x, y3);
    
    if ((tiles_1 != 0x7A) && (tiles_1 != 0xFF)) {
       return TRUE;
    }

    if ((tiles_3 != 0x7A) && (tiles_1 != 0xFF)) {
        return TRUE;
    }

    return FALSE;
}




BYTE right_collision(UINT16 world_x, UINT16 world_y) {

    return FALSE;

   UINT16 x  = world_x + 15;    // borde derecho
   UINT16 y1 = world_y - 7;
   UINT16 y2 = world_y;
   UINT16 y3 = world_y + 7;


    UINT8 tiles_1 = get_tile_at_world(x, y1);
    UINT8 tiles_2 = get_tile_at_world(x, y2);
    UINT8 tiles_3 = get_tile_at_world(x, y3);

    
    if ((tiles_1 != 0x7A) && (tiles_1 != 0xFF)) {
       return TRUE;
    }

    if ((tiles_3 != 0x7A) && (tiles_3 != 0xFF)) {
        return TRUE;
    }

    return FALSE;
}

BYTE nomove_collision(UINT16 world_x, UINT16 world_y) {

  return FALSE;

   UINT16 x  = world_x + 7;    // borde derecho
   UINT16 y1 = world_y - 7;
   UINT16 y2 = world_y;
   UINT16 y3 = world_y + 7;


    UINT8 tiles_1 = get_tile_at_world(x, y1);
    UINT8 tiles_2 = get_tile_at_world(x, y2);
    UINT8 tiles_3 = get_tile_at_world(x, y3);
    
    if ((tiles_1 != 0x7A) && (tiles_1 != 0xFF)) {
       return TRUE;
    }

    if ((tiles_3 != 0x7A) && (tiles_3 != 0xFF)) {
        return TRUE;
    }

    return FALSE;
}
*/







/*
BYTE movePlayer(UINT16 scroll_x) {

   UINT16 world_x = 0;
   UINT16 world_y = 0;    

   UINT8 dx = 0;
   UINT8 dy = 0;

   if (joypad() & J_LEFT && elements[PLAYER_ID].x > 8) {
       world_x =  elements[PLAYER_ID].x + scroll_x - elements[PLAYER_ID].inc;
       world_y =  elements[PLAYER_ID].y;
       if (!left_collision(world_x, world_y)) {
           dx = -elements[PLAYER_ID].inc;
       } else {
           return TRUE;
       } 
   }

   if (joypad() & J_RIGHT && (elements[PLAYER_ID].x + elements[PLAYER_ID].width) < 168) {
       world_x =  elements[PLAYER_ID].x + scroll_x + elements[PLAYER_ID].inc;
       world_y =  elements[PLAYER_ID].y;
       if (!right_collision(world_x, world_y)) {
           dx =  elements[PLAYER_ID].inc;
       } else {
           return TRUE;
      } 
   } 

   if (joypad() & J_UP && elements[PLAYER_ID].y > 16) {
       world_x = elements[PLAYER_ID].x;
       world_y = elements[PLAYER_ID].y - elements[PLAYER_ID].inc;
       if (!up_collision(world_x, world_y)) {
           dy = -elements[PLAYER_ID].inc;
       } else {
           return TRUE;
       } 
       
   }

   if (joypad() & J_DOWN && (elements[PLAYER_ID].y + elements[PLAYER_ID].height) < 152) {
      
       world_x = elements[PLAYER_ID].x;
       world_y = elements[PLAYER_ID].y + elements[PLAYER_ID].inc;
       if (!down_collision(world_x, world_y)) {
          dy = elements[PLAYER_ID].inc;
       } else {
          return TRUE;
       } 
   }

   world_x = elements[PLAYER_ID].x + scroll_x;
   world_y = elements[PLAYER_ID].y;

   if (nomove_collision(world_x, world_y)) {
       return TRUE; 
   }
        
   elements[PLAYER_ID].x += dx;
   elements[PLAYER_ID].y += dy;

 
    moveTilePlayer();

    return FALSE;
}
*/