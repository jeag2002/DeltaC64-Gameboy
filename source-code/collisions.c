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


UINT8 getTileAtWorld(UINT16 world_x, UINT16 world_y) {

    UINT16 wx = (world_x >> 3) - 1;
    UINT16 wy = (world_y >> 3) - 2;

    return background_map_3[wy * MAP_WIDTH_TILE + wx];
}

UINT8 downCollisionEnv(UINT16 world_x, UINT16 world_y, UINT16 height) {
    return getTileAtWorld(world_x, world_y + height);
}

UINT8 upCollisionEnv(UINT16 world_x, UINT16 world_y) {
    return getTileAtWorld(world_x, world_y);
}

UINT8 leftCollisionEnv(UINT16 world_x, UINT16 world_y){
    return getTileAtWorld(world_x, world_y);
}

UINT8 rightCollisionEnv(UINT16 world_x, UINT16 world_y, UINT16 width){
    return getTileAtWorld((world_x + width), world_y);
}

UINT8 noMoveCollisionEnv(UINT16 world_x, UINT16 world_y, UINT16 width){
    return getTileAtWorld((world_x + width), world_y);
}

