#ifndef GAMEBUILDER_H
#define GAMEBUILDER_H

#include <gb/gb.h>
#include <stdint.h>
#include "global.h"


/// @brief 
extern unsigned char hud_line[];

UINT16 getWorldScroll();
void setHUD(UINT8 score, UINT8 lives);
void performantDelay(UINT8 numloops);
void launchLevel(int level);
void incWorldScroll();

BYTE stepLevel();

#endif