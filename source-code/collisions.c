#include <gb/gb.h>
#include "collisions.h"
#include "global.h"
#include "world.h"

unsigned char *background_map_3;

void setCollBoundaries(int level) {
    background_map_3 = getLevelFromIndex(level);
}

//B2B collision box detection.
UBYTE isCollisionB2B(UINT16 elem_1_x, UINT16 elem_1_y,
                     UINT16 elem_1_w, UINT16 elem_1_h,
                     UINT16 elem_2_x, UINT16 elem_2_y,
                     UINT16 elem_2_w, UINT16 elem_2_h) {

    return (elem_1_x >= elem_2_x && elem_1_x <= elem_2_x + elem_2_w) 
    && (elem_1_y >= elem_2_y && elem_1_y <= elem_2_y + elem_2_h) 
    || (elem_2_x >= elem_1_x && elem_2_x <= elem_1_x + elem_1_w) 
    && (elem_2_y >= elem_1_y && elem_2_y <= elem_1_y + elem_1_h);
}

/**
 * COLLIDE ELEMENT DETECTION.
 * @brief only specific blocks can be detected as collided (from 0x26 to 0x79), EXCEPT 0x7A
 * 
 * @param tile 
 * @return BYTE 
 */
BYTE isCollideElement(UINT8 tile) {
    return (tile >= TILE_COLLIDE_INF) && (tile <= TILE_COLLIDE_SUP) && (tile != TILE_EMPTY);         
}


//DELETE BONUS TILES FROM BACKGROUND IF PLAYER COLLISIONED 
void processBackGroundTile (UINT8 TILE, UINT16 wx, UINT16 wy) {
    if ((TILE == TILE_SHOOT_1_1) || (TILE == TILE_SHOOT_2_1) || (TILE == TILE_SHOOT_3_1) || (TILE == TILE_SHOOT_S_1)) {
        background_map_3[wy * MAP_WIDTH_TILE + wx] = 0x7A;
        background_map_3[wy * MAP_WIDTH_TILE + (wx + 1)] = 0x7A;
        background_map_3[(wy + 1) * MAP_WIDTH_TILE + (wx + 1)] = 0x7A;
        background_map_3[(wy + 1) * MAP_WIDTH_TILE + wx] = 0x7A;

    } else if ((TILE == TILE_SHOOT_1_2) || (TILE == TILE_SHOOT_2_2) || (TILE == TILE_SHOOT_3_2) || (TILE == TILE_SHOOT_S_2)) {
        background_map_3[wy * MAP_WIDTH_TILE + wx] = 0x7A;
        background_map_3[wy * MAP_WIDTH_TILE + (wx - 1)] = 0x7A;
        background_map_3[(wy + 1) * MAP_WIDTH_TILE + (wx - 1)] = 0x7A;
        background_map_3[(wy + 1) * MAP_WIDTH_TILE + wx] = 0x7A;

    } else if ((TILE == TILE_SHOOT_1_3) || (TILE == TILE_SHOOT_2_3) || (TILE == TILE_SHOOT_3_3) || (TILE == TILE_SHOOT_S_3)) {
        background_map_3[wy * MAP_WIDTH_TILE + wx] = 0x7A;
        background_map_3[wy * MAP_WIDTH_TILE + (wx + 1)] = 0x7A;
        background_map_3[(wy - 1) * MAP_WIDTH_TILE + (wx + 1)] = 0x7A;
        background_map_3[(wy - 1) * MAP_WIDTH_TILE + wx] = 0x7A;


    } else if ((TILE == TILE_SHOOT_1_4) || (TILE == TILE_SHOOT_2_4) || (TILE == TILE_SHOOT_3_4) || (TILE == TILE_SHOOT_S_4)) {
        background_map_3[wy * MAP_WIDTH_TILE + wx] = 0x7A;
        background_map_3[wy * MAP_WIDTH_TILE + (wx - 1)] = 0x7A;
        background_map_3[(wy - 1) * MAP_WIDTH_TILE + (wx - 1)] = 0x7A;
        background_map_3[(wy - 1) * MAP_WIDTH_TILE + wx] = 0x7A;
    }

}

//DETECT TILE AT WORLD
CollisionData *getTileAtWorld(UINT16 world_x, UINT16 world_y, UINT8 type) {

    CollisionData returnData;
    
    UINT16 wx = (world_x >> 3) - 1;
    UINT16 wy = (world_y >> 3) - 2;


    returnData.x = wx;
    returnData.y = wy;
    returnData.TILE = background_map_3[wy * MAP_WIDTH_TILE + wx];
    if (type == TYPE_PLAYER) {
        processBackGroundTile (returnData.TILE, returnData.x, returnData.y);
    }

    return &returnData;
}

CollisionData *downCollisionEnv(UINT16 world_x, UINT16 world_y, UINT16 height) {
    return getTileAtWorld(world_x, (world_y + height), TYPE_PLAYER);
}

CollisionData *upCollisionEnv(UINT16 world_x, UINT16 world_y) {
    return getTileAtWorld(world_x, world_y, TYPE_PLAYER);
}

CollisionData *leftCollisionEnv(UINT16 world_x, UINT16 world_y){
    return getTileAtWorld(world_x, world_y, TYPE_PLAYER);
}

CollisionData *rightCollisionEnv(UINT16 world_x, UINT16 world_y, UINT16 width){
    return getTileAtWorld((world_x + width), world_y, TYPE_PLAYER);
}

CollisionData *noMoveCollisionEnv(UINT16 world_x, UINT16 world_y, UINT16 width){
    return getTileAtWorld((world_x + width), world_y, TYPE_PLAYER);
}

CollisionData *noMoveCollisionShoot(UINT16 world_x, UINT16 world_y, UINT16 width, UINT8 type){
    return getTileAtWorld((world_x + width), world_y, type);
}



