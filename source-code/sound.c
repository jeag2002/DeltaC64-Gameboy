#include "sound.h"
#include <gb/gb.h>
#include <stdio.h>
#include <stdint.h>


#define NR10_REG (*(volatile uint8_t*)0xFF10)
#define NR11_REG (*(volatile uint8_t*)0xFF11)
#define NR12_REG (*(volatile uint8_t*)0xFF12)
#define NR13_REG (*(volatile uint8_t*)0xFF13)
#define NR14_REG (*(volatile uint8_t*)0xFF14)

#define NR21_REG (*(volatile uint8_t*)0xFF16)
#define NR22_REG (*(volatile uint8_t*)0xFF17)
#define NR23_REG (*(volatile uint8_t*)0xFF18)
#define NR24_REG (*(volatile uint8_t*)0xFF19)

#define NR41_REG (*(volatile uint8_t*)0xFF20)
#define NR42_REG (*(volatile uint8_t*)0xFF21)
#define NR43_REG (*(volatile uint8_t*)0xFF22)
#define NR44_REG (*(volatile uint8_t*)0xFF23)

#define NR50_REG (*(volatile uint8_t*)0xFF24)
#define NR51_REG (*(volatile uint8_t*)0xFF25)
#define NR52_REG (*(volatile uint8_t*)0xFF26)

static inline void sound_power_on() {
    NR52_REG |= 0x80; // encender audio
    NR50_REG = 0x77;  // volumen global L+R
    NR51_REG = 0xFF;  // todos los canales en L+R
}

void play_laser_type(uint8_t type) {
    uint16_t freq = 0;

    switch(type) {
        case 0: // Laser A – “pew” corto descendente
            NR10_REG = 0x17; // sweep rápido descendente
            NR11_REG = 0x40; // duty 25%
            NR12_REG = 0xF1; // vol 15, decay rápido
            freq = 950;
            break;

        case 1: // Laser B – “zap” más grave
            NR10_REG = 0x14; // sweep descendente lento
            NR11_REG = 0x80; // duty 50%
            NR12_REG = 0xE3; // vol 14, decay medio
            freq = 600;
            break;

        case 2: // Laser C – “piu” agudo
            NR10_REG = 0x00; // sin sweep
            NR11_REG = 0xC0; // duty 75%
            NR12_REG = 0xF2; // vol 15, decay medio-rápido
            freq = 1200;
            break;

        default:
            return;
    }

    // Escribir frecuencia y disparar
    NR13_REG = (uint8_t)(freq & 0xFF);
    NR14_REG = 0xC0 | ((freq >> 8) & 0x07);
}

void play_explosion_type(uint8_t type) {
    NR41_REG = 0x3F; // length máx

    switch(type) {
        case 0: // "boom" grave
            NR42_REG = 0xF2; // vol 15, decay medio-rápido
            NR43_REG = 0x3F; // ruido grave
            break;

        case 1: // "crash" chisporroteante
            NR42_REG = 0xF4; // vol 15, decay largo
            NR43_REG = 0x7F; // ruido fino
            break;

        case 2: // "ka-pow" medio
            NR42_REG = 0xE3; // vol 14, decay medio
            NR43_REG = 0x5F; // ruido medio
            break;

        default: return;
    }

    // Reinicio del trigger (IMPORTANTE para que suene siempre)
    NR44_REG = 0x00; // limpiar bit 7
    NR44_REG = 0xC0; // trigger (bit 7 = 1)
}

void play_ding() {
    // Canal 1 (NR10–NR14)
    NR10_REG = 0x00;   // sin sweep
    NR11_REG = 0x80;   // duty 50%
    NR12_REG = 0xF2;   // volumen inicial 15, decay medio-rápido
    NR13_REG = 0xF0;   // frecuencia baja bits
    NR14_REG = 0xC5;   // frecuencia alta bits + trigger
}
