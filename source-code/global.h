#ifndef GLOBAL_H
#define GLOBAL_H

//SCREEN BOUNDARIES
#define LIMIT_BOUNDARY_X_INF 8
#define LIMIT_BOUNDARY_X_SUP 168 
#define LIMIT_BOUNDARY_Y_INF 16
#define LIMIT_BOUNDARY_Y_SUP 152

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

//LEVELS
#define NUMLEVELS 5

//MAX STOP BACKGROUND FRAME.
#define STOPS 3

//MAX NUM GROUPS OF ENEMIES BY STOP.
#define NUM_GROUP_ENEMIES_BY_STOP 1

//MAX NUM ENEMIES BY GROUP
#define NUMENEMIES 4

//MAX STEPS ENEMIES
#define NUMSTEPS 20

//SPECIFIC TILES
#define TILE_EMPTY 0x7A
#define TILE_COLLIDE_INF 0x26
#define TILE_COLLIDE_SUP 0x79

//SHOTS VARIABLES
///////////////////////////////////////////////////////
//TILE x 1 SHOOT MODE
#define TILE_SHOOT_1_1 0x3A
#define TILE_SHOOT_1_2 0x3B
#define TILE_SHOOT_1_3 0x3C
#define TILE_SHOOT_1_4 0x3D

//TILE x 2 SHOOT MODE
#define TILE_SHOOT_2_1 0x76
#define TILE_SHOOT_2_2 0x77
#define TILE_SHOOT_2_3 0x78
#define TILE_SHOOT_2_4 0x79

//TILE x 3 SHOOT MODE
#define TILE_SHOOT_3_1 0x4E
#define TILE_SHOOT_3_2 0x4F
#define TILE_SHOOT_3_3 0x50
#define TILE_SHOOT_3_4 0x51

//TILE x SPECIAL SHOOT MODE
#define TILE_SHOOT_S_1 0x2A
#define TILE_SHOOT_S_2 0x2B
#define TILE_SHOOT_S_3 0x2C
#define TILE_SHOOT_S_4 0x2D
/////////////////////////////////////////////////////////////////


//PLAYER
#define PLAYER_POS_X_INI 80
#define PLAYER_POS_Y_INI 80

//POS ENEMIES
#define ENEMY_POS_X_INI 116;
#define ENEMY_POS_Y_INI 80;

//SIZES (ALL SIZE THE SAME)
#define ELEMENT_WIDTH 16
#define ELEMENT_HEIGHT 16

//NO VALUE
#define NO_VALUE 0

//INC MOVEMENT PLAYER
#define INC_PLAYER 1
//SCORE
#define SCORE_PLAYER 0
//LIVES
#define LIVES_PLAYER 3
//TYPE SHOOT
#define NO_SHOOT 0

//STOP ID
#define NO_STOP 0
//GROUP ID
#define NO_GROUP 0
//GROUP ID INDEX
#define NO_GROUP_INDEX 0

//LEVELS
#define LEVEL_1_INDEX 1

//TYPE ELEMENTS
#define TYPE_PLAYER 0
#define TYPE_ENEMY 1
#define TYPE_SHOOT_PLAYER 2
#define TYPE_SHOOT_ENEMY 3

//TYPE ENEMIES
#define TYPE_ENEMY_PLANET 11
#define TYPE_ENEMY_STAR 12
#define TYPE_ENEMY_OVNI 13




//STRUCTURE ELEMENTS
///////////////////////////////////////////////////////////////
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

    UINT8 type;

    UINT8 stop_id;    
    UINT8 enemy_id;

    UINT8 lives;
    UINT8 scores;

    UINT8 type_shoot;

    UINT8 width;
    UINT8 height;
};


typedef struct Element ElementType;
extern ElementType elements[NUMELEMENTS];
///////////////////////////////////////////////////////////////




//STRUCTURE GROUP ELEMENTS
///////////////////////////////////////////////////////////////

typedef struct {
    INT8 x;
    INT8 y;
} Coordinate;

typedef struct {
    Coordinate movement[NUMENEMIES];
} MovementType;

typedef struct {
    UINT8 num_enemies;
    UINT8 type_enemy;
    UINT8 num_frames;
    UINT8 steps;
    MovementType *behav_enemy;
} EnemyGroupType;

typedef struct {
    INT16 stop;
    BYTE processed;
    EnemyGroupType enemiesByStop;
} EnemyEntryType;

typedef struct {
    UINT8 id;
    UINT8 numstops;
    EnemyEntryType stops[STOPS];
} LevelType;

///////////////////////////////////////////////////////////

#endif