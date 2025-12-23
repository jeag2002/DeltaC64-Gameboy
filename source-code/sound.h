#include <gb/gb.h>

#ifndef SOUND_H
#define SOUND_H

static inline void sound_power_on();
void play_laser_type(uint8_t type);
void play_explosion_type(uint8_t type);
void play_ding();

#endif