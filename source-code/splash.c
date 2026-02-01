#include <gb/gb.h>
#include <stdio.h>
#include <gb/font.h>
#include <gb/cgb.h> 
#include <stdint.h>
#include <string.h>
#include "splash_map.h"
#include "splash_tile_map.h"


//extern const unsigned char *song_Data[];


#define BY_TEXT               "BY JOAN"
#define BY_OAM_BASE           5     // sprites 0..4 ocupados por START
#define BY_FIRST_SPR_TILE     220   // evita solapar con otros tiles
#define SPLASH_SPRITE_COUNT   20 

#define SPR_PAL(p) ((_cpu == CGB_TYPE) ? ((p) & 0x07) : ((p) ? 0x10 : 0x00))

// Solo necesitamos los glifos que aparecen en el texto (y espacio)
enum { G_SPC, G_A, G_B, G_J, G_N, G_O, G_Y, G_COUNT };

// Tiles 8x8 (2bpp) para A,B,C,J,L,N,O,R,Y,Z y espacio.
// (estilo simple; puedes afinar el arte si quieres)
const unsigned char BY_glyph_tiles[G_COUNT * 16] = {
    // ' ' (vacío)
    0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,
    // 'A'
    0,0, 24,0, 36,0, 60,0, 36,0, 36,0, 36,0, 0,0,
    // 'B'
    0,0, 56,0, 36,0, 56,0, 36,0, 36,0, 56,0, 0,0,
    // 'J'
    0,0, 12,0, 12,0, 12,0, 36,0, 36,0, 24,0, 0,0,
    // 'N'
    0,0, 36,0, 52,0, 44,0, 36,0, 36,0, 36,0, 0,0,
    // 'O'
    0,0, 24,0, 36,0, 36,0, 36,0, 36,0, 24,0, 0,0,
    // 'Y'
    0,0, 36,0, 24,0, 24,0, 24,0, 24,0, 0,0, 0,0

};


#define START_FIRST_SPR_TILE  200  // índice de tile en VRAM para los sprites (evitar solapar con BG)
#define START_LEN             5    // S,T,A,R,T

// Tiles 2bpp (DMG) para "S","T","A","R","T" como sprites 8x8.
// Cada fila = (low byte, high byte). Usamos color 1 (low=1, high=0) => visible y “blanco” con paleta adecuada.


const unsigned char START_spr_tiles[START_LEN * 16] = {
    // 'S'
    124,0,  64,0,  120,0,  4,0,  4,0,  4,0,  120,0,  0,0,
    // 'T'
    124,0,  16,0,  16,0,   16,0, 16,0,  16,0, 16,0,   0,0,
    // 'A'
    56,0,   68,0,  124,0,  68,0, 68,0,  68,0, 68,0,   0,0,
    // 'R'
    120,0,  68,0,  120,0,  68,0, 68,0,  68,0, 68,0,   0,0,
    // 'T'
    124,0,  16,0,  16,0,   16,0, 16,0,  16,0, 16,0,   0,0
};

// Helpers para convertir coordenadas de tiles a píxeles de pantalla (zona visible GB)
#define TILE_TO_X(tx) ((uint8_t)(8  + ((tx) << 3)))  // margen X visible empieza en 8px
#define TILE_TO_Y(ty) ((uint8_t)(16 + ((ty) << 3)))  // margen Y visible empieza en 16px


uint8_t glyph_index(char c) {
    switch(c) {
        case ' ': return G_SPC;
        case 'A': return G_A;
        case 'B': return G_B;
        case 'J': return G_J;
        case 'N': return G_N;
        case 'O': return G_O;
        case 'Y': return G_Y;
        default:  return G_SPC; // por si acaso
    }
}

void place_start_sprites(uint8_t x_px, uint8_t y_px) {
    // Cargar data de sprites para START
    set_sprite_data(START_FIRST_SPR_TILE, START_LEN, START_spr_tiles);

    // Asignar tiles a 5 sprites consecutivos y colocarlos
    for (uint8_t i = 0; i < START_LEN; i++) {
        set_sprite_tile(i, START_FIRST_SPR_TILE + i);
        set_sprite_prop(i, SPR_PAL(0));  
        move_sprite(i, (uint8_t)(x_px + (i * 8)), y_px);
    }
}

void place_text_sprites(const char* s, uint8_t oam_base, uint8_t x_px, uint8_t y_px) {
    // cargar set de glifos
    set_sprite_data(BY_FIRST_SPR_TILE, G_COUNT, BY_glyph_tiles);

    uint8_t oam = oam_base;
    uint8_t x = x_px;

    for (const char* p = s; *p; ++p) {
        uint8_t g = glyph_index(*p);
        if (*p != ' ') { // espacio: solo avanzar
            set_sprite_tile(oam, (uint8_t)(BY_FIRST_SPR_TILE + g));
            set_sprite_prop(oam, SPR_PAL(1));   // usar paleta OBJ1
            move_sprite(oam, x, y_px);
            oam++;
        }
        x = (uint8_t)(x + 6);
    }
}


void hide_start_sprites(void) {
    // Moverlos fuera de la zona visible (y=0 oculta el sprite)
    for (uint8_t i = 0; i < START_LEN; i++) move_sprite(i, 0, 0);
}

void hide_all_start_sprites(void) {
    // Moverlos fuera de la zona visible (y=0 oculta el sprite)
    for (uint8_t i = 0; i < SPLASH_SPRITE_COUNT; i++) move_sprite(i, 0, 0);
}

void show_start_sprites(uint8_t x_px, uint8_t y_px) {
    for (uint8_t i = 0; i < START_LEN; i++) move_sprite(i, (uint8_t)(x_px + (i * 8)), y_px);
}

void processSplash() {
    
    DISPLAY_OFF;
    HIDE_BKG;
    HIDE_WIN;
    HIDE_SPRITES;
    
    set_bkg_data(0, 114, splash_tile_map);
    set_bkg_tiles(0, 0, 20, 18, splash_map);


    //INVERSION DE COLORES (PARA VERLO MEJOR EN DISPOSITIVO!)
    BGP_REG  = 0x1B; // invertido de 0xE4 (si ese era tu BGP)
    OBP0_REG = 0x1F; // invertido de 0xE0
    OBP1_REG = 0x1B; // invertido de 0xE4


    //OBP0_REG = 0xE0; // 11 10 00 00  => col3 negro, col2 gris oscuro, col1 blanco, col0 blanco(transparente)
    //OBP1_REG = 0xE4;

    // --- 2) Config de pantalla ---
                // cambio de registros seguro
    SHOW_BKG;
    SHOW_SPRITES;
    SPRITES_8x8;            // usamos sprites 8x8
    DISPLAY_ON;


    //-->musica

    const uint8_t tx = 8;       // columna
    const uint8_t ty = 15;      // fila
    const uint8_t start_x = TILE_TO_X(tx);
    const uint8_t start_y = TILE_TO_Y(ty);

    place_start_sprites(start_x, start_y);

    const char* bytxt = BY_TEXT;
    uint8_t by_tx = 7;
    uint8_t by_ty = 12;
    uint8_t by_x  = TILE_TO_X(by_tx);
    uint8_t by_y  = TILE_TO_Y(by_ty);

    place_text_sprites(bytxt, BY_OAM_BASE, by_x, by_y);


    // --- 5) Bucle + parpadeo ---
    uint8_t visible = 1;
    uint8_t ctr = 0;

    BOOLEAN DONE = FALSE;

    while (DONE == FALSE) {
        wait_vbl_done();
        ctr++;

        // ~30 frames ≈ 0.5 s a 60 FPS (DMG)
        if (ctr >= 30) {
            ctr = 0;
            visible = !visible;
            if (visible) show_start_sprites(start_x, start_y);
            else         hide_start_sprites();
        }

        // (Opcional) salir si se pulsa START para ir a tu siguiente pantalla
        if (joypad() & J_START) {
            DONE = TRUE;
        }
    }

    hide_all_start_sprites();
}