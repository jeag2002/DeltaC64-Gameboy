#include <gb/gb.h>
#include "global.h"

#ifndef COLLISIONS_H
#define COLLISIONS_H

//SET MAP TO COLLISION ENGINE
void setCollBoundaries(int level);

//IS A TILE COLLIDEABLE?
BYTE isCollideElement(UINT8 tile);

//COLLISION BETWEEN TWO ELEMENTS
UBYTE isCollisionB2B(UINT16 elem_1_x, UINT16 elem_1_y,
                     UINT16 elem_1_w, UINT16 elem_1_h,
                     UINT16 elem_2_x, UINT16 elem_2_y,
                     UINT16 elem_2_w, UINT16 elem_2_h);

//COLL WHEN DOWN
UINT8 downCollisionEnv(UINT16 world_x, UINT16 world_y, UINT16 height);
//COLL WHEN UP
UINT8 upCollisionEnv(UINT16 world_x, UINT16 world_y);
//COLL WHEN LEFT
UINT8 leftCollisionEnv(UINT16 world_x, UINT16 world_y);
//COLL WHEN RIGHT
UINT8 rightCollisionEnv(UINT16 world_x, UINT16 world_y, UINT16 width);
//COLL WHEN NO MOVE
UINT8 noMoveCollisionEnv(UINT16 world_x, UINT16 world_y, UINT16 width);






#endif

