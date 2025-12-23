#ifndef GLOBAL_H
#define GLOBAL_H

//SIZE STANDARD MAP IN TILES
#define MAP_WIDTH_TILE       160
#define MAP_HEIGHT_TILE      18

//SIZE SCREEN PX
#define SCREEN_WIDTH         160
#define SCREEN_HEIGHT        144

//SIZE SCREEN TILES
#define SCREEN_WIDTH_TILE    20
#define SCREEN_HEIGHT_TILE   18

//SIZE TILES
#define TILE_SIZE            8

//SIZE STANDARD MAP IN PX
#define MAP_W_PX   (MAP_WIDTH_TILE * TILE_SIZE)
#define MAP_H_PX   (MAP_HEIGHT_TILE * TILE_SIZE)

//PARTS OF FRAME ANIMATION
#define PICS 4

//NUM FRAME ANIMATION
#define FRAMES 4

//NUM ELEMENTS BUFFER
#define NUMELEMENTS 20

//ID PLAYER_ID
#define PLAYER_ID 0

//NUM FRAMES PLAYER
#define NUM_FRAMES_PLAYER 4

//NUM IMAGES x FRAMES 
#define NUM_IMAGES_BY_FRAME_PLAYER 4

//INC MOVEMENT PLAYER
#define INC_PLAYER 1
//SCORE
#define SCORE_PLAYER 0
//LIVES
#define LIVES_PLAYER 3
//TYPE SHOOT
#define NO_SHOOT 0
//GROUP ID
#define NO_GROUP 0
//GROUP ID INDEX
#define NO_GROUP_INDEX 0

//LEVELS
#define LEVEL_1_INDEX 1




struct Frame {
    UINT8 spritids[PICS];  //frame component
    UINT8 num_spritids;    //num part of frames
};

//PLAYER, ENEMIES, BULLETS.
struct Element {
    struct Frame numFrames[FRAMES]; //numframes x component
    
    UINT8 current_index; //index image
    UINT8 current_frame; //index frame
    UINT8 num_frames;    //num frames.

    UINT8 inc;
    BYTE disabled;

    UINT8 x;
    UINT8 x_world;
    UINT8 y;

    UINT8 group_id;
    UINT8 group_id_index;

    UINT8 lives;
    UINT8 scores;

    UINT8 type_shoot;

    UINT8 width;
    UINT8 height;
};


typedef struct Element ElementType;
extern ElementType elements[NUMELEMENTS];


#endif