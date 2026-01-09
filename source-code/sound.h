#include <gb/gb.h>

#ifndef SOUND_H
#define SOUND_H

typedef enum {
    SND_NONE = 0,
    SND_LASER_A,
    SND_LASER_B,
    SND_EXPLOSION_A,
    SND_EXPLOSION_B,
    SND_DING
} SoundEvent;

void sound_request(SoundEvent ev);
void sound_dispatch(void);

void sound_power_on();
void play_laser_type(uint8_t type);
void play_explosion_type(uint8_t type);
void play_ding();

#endif