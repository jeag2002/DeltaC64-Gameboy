#include "captions.h"
#include <gb/gb.h>
#include <string.h>
#include <gb/font.h>


#define MSG_SPRITE_BASE 200    // primer tile usado por el mensaje
#define MSG_SPRITE_COUNT 9     // "LEVEL ONE" = 9 caracteres
#define MSG_X_START 40         // posición horizontal inicial (en píxeles)
#define MSG_Y 72               // posición vertical (centro aprox.)
#define MSG_DURATION 120       // frames visibles (~2 s)

#define LEVEL_ONE_LEN 9

#define SPR_PAL(p) ((_cpu == CGB_TYPE) ? ((p) & 0x07) : ((p) ? 0x10 : 0x00))

// ---------------------------------------------------------
// TILES: letras blancas sobre fondo negro
// Cada tile 8x8, 1 bit color, diseñado directamente en VRAM
// ---------------------------------------------------------

const unsigned char level_one_spr_tiles[LEVEL_ONE_LEN * 16] = {
    // 'L'
    128,0,  128,0,  128,0,  128,0,  128,0,  128,0,  255,0,  0,0,
    // 'E'
    255,0,  128,0,  128,0,  255,0,  128,0,  128,0,  255,0,  0,0,
    // 'V'
    129,0,  129,0,  66,0,   66,0,   36,0,   36,0,   24,0,   0,0,
    // 'E'
    255,0,  128,0,  128,0,  255,0,  128,0,  128,0,  255,0,  0,0,
    // 'L'
    128,0,  128,0,  128,0,  128,0,  128,0,  128,0,  255,0,  0,0,
    // ESPACIO
    0,0,    0,0,    0,0,    0,0,    0,0,    0,0,    0,0,    0,0,
    // 'O'
    255,0,  129,0,  129,0,  129,0,  129,0,  129,0,  255,0,  0,0,  
    // 'N'
    193,0,  161,0,  145,0,  137,0,  133,0,  131,0,  129,0,  0,0,
    // 'E'
    255,0,  128,0,  128,0,  255,0,  128,0,  128,0,  255,0,  0,0
};

/*
const unsigned char msg_tiles[] = {
    // L (tile 0)
    0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xFF,
    // E (tile 1)
    0xFF,0x81,0x81,0xFF,0x81,0x81,0x81,0xFF,
    // V (tile 2)
    0x81,0x81,0x81,0x42,0x24,0x18,0x18,0x18,
    // O (tile 3)
    0x7E,0x81,0x81,0x81,0x81,0x81,0x81,0x7E,
    // N (tile 4)
    0x81,0xC1,0xA1,0x91,0x89,0x85,0x83,0x81,
    // E (tile 5)
    0xFF,0x81,0x81,0xFF,0x81,0x81,0x81,0xFF,
    // Espacio (tile 6)
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
*/

// Texto "LEVEL ONE" → índices de tiles
//const UINT8 msg_map[] = { 0,1,2,1,0,6,3,4,5 };

// ---------------------------------------------------------
// Mostrar mensaje "LEVEL ONE" con sprites
// ---------------------------------------------------------
void show_level_one_msg() {

    UINT8 x_px = MSG_X_START;
    UINT8 y_px = MSG_Y;

     // Cargar data de sprites para START
    set_sprite_data(MSG_SPRITE_BASE, LEVEL_ONE_LEN, level_one_spr_tiles);

    // Asignar tiles a 5 sprites consecutivos y colocarlos
    for (uint8_t i = 0; i < LEVEL_ONE_LEN; i++) {
        set_sprite_tile(i, MSG_SPRITE_BASE + i);
        set_sprite_prop(i, SPR_PAL(0));  
        move_sprite(i, (uint8_t)(x_px + (i * 8) + 2), y_px);
    }

    /*
    set_sprite_data(MSG_SPRITE_BASE, 7, msg_tiles);

    UINT8 x = MSG_X_START;
    for (UINT8 i = 0; i < MSG_SPRITE_COUNT; i++) {
        set_sprite_tile(i, MSG_SPRITE_BASE + msg_map[i]);
        move_sprite(i, x, MSG_Y);
        x += 8; // cada sprite 8 px
    }
    */

}

// Ocultar mensaje (mover fuera de pantalla)
void hide_level_one_msg() {
    for (UINT8 i = 0; i < MSG_SPRITE_COUNT; i++) {
        move_sprite(i, 0, 0);
    }
}

// Espera sin interrumpir VBlank
void wait_frames_level_one(UINT16 frames) {
    for (UINT16 i = 0; i < frames; i++) wait_vbl_done();
}





/*
// ====== CONFIG ======
#define MSG_TILE_BASE 240  // bloque alto, fuera del rango de tu tileset/HUD
// Posición en ventana (tiles) donde saldrá "LEVEL ONE"
#define MSG_WIN_X 5
#define MSG_WIN_Y 7
// Duración en frames (~2s @60fps)
#define MSG_DURATION 120

// ====== TILES DEL MENSAJE (blanco sobre negro, 8x8) ======
// 0: 'L', 1: 'E', 2: 'V', 3: 'O', 4: 'N', 5:'E'(rep), 6:' ' (espacio)
const unsigned char msg_tiles[] = {
    // 'L'
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x81,0x81,
    // 'E'
    0x81,0x81,0x81,0x81,0xFF,0x81,0x81,0xFF,
    // 'V'
    0x81,0x81,0x81,0x42,0x24,0x18,0x18,0x18,
    // 'O'
    0x7E,0x81,0x81,0x81,0x81,0x81,0x81,0x7E,
    // 'N'
    0x81,0xC1,0xA1,0x91,0x89,0x85,0x83,0x81,
    // 'E' (de nuevo, mismo bitmap que 1)
    0x81,0x81,0x81,0x81,0xFF,0x81,0x81,0xFF,
    // ' ' (espacio = todo negro para “transparente” sobre fondo negro)
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
};

// Mapa del texto "LEVEL ONE" en índices relativos (0..6)
const unsigned char msg_map_rel[] = { 0,1,2,1,0,6,3,4,5 };
#define MSG_LEN (sizeof(msg_map_rel))

// Buffer para restaurar el HUD de la ventana donde pintamos el mensaje
unsigned char win_backup[MSG_LEN];

// ====== UTILIDADES ======
void wait_frames_load_caption(UINT16 f){ while(f--) wait_vbl_done(); }

// ====== CARGA DE TILES DEL MENSAJE ======
// Llama a esto DESPUÉS de cargar tu tileset del juego.
void message_load_tiles() {
    // Carga 7 tiles a partir de MSG_TILE_BASE en el banco de patrones BG/WIN
    set_bkg_data(MSG_TILE_BASE, 7, msg_tiles);
}

// ====== MOSTRAR / OCULTAR MENSAJE EN VENTANA SIN TOCAR EL HUD ======
void message_show_level_one() {
    // 1) Hacer backup de lo que haya en esa franja de la ventana
    get_win_tiles(MSG_WIN_X, MSG_WIN_Y, MSG_LEN, 1, win_backup);

    // 2) Construir el array de IDs ABSOLUTOS de tiles (sumando MSG_TILE_BASE)
    unsigned char ids[MSG_LEN];
    for (UINT8 i = 0; i < MSG_LEN; i++) {
        ids[i] = MSG_TILE_BASE + msg_map_rel[i];
    }

    // 3) Escribir el mensaje SOLO en esa zona de la ventana
    set_win_tiles(MSG_WIN_X, MSG_WIN_Y, MSG_LEN, 1, ids);
}

void message_hide_level_one() {
    // Restaurar exactamente lo que había (HUD intacto)
    set_win_tiles(MSG_WIN_X, MSG_WIN_Y, MSG_LEN, 1, win_backup);
}
*/


/*
#include <string.h>
#include <gb/font.h>


// ---------------------------------------------------------
// FUENTE: letras blancas sobre fondo negro (1 bit por pixel)
// Cada letra es 8x8 pixeles
// ---------------------------------------------------------
const unsigned char white_font_tiles[] = {
    // Letra L (tile 0)
    0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,
    // Letra E (tile 1)
    0xFF,0x81,0x81,0xFF,0x81,0x81,0x81,0xFF,
    // Letra V (tile 2)
    0x81,0x81,0x81,0x42,0x24,0x18,0x18,0x18,
    // Letra O (tile 3)
    0x7E,0x81,0x81,0x81,0x81,0x81,0x81,0x7E,
    // Letra N (tile 4)
    0x81,0xC1,0xA1,0x91,0x89,0x85,0x83,0x81,
    // Letra E (tile 5) (repetida)
    0xFF,0x81,0x81,0xFF,0x81,0x81,0x81,0xFF,
    // Espacio (tile 6)
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

// Mapa del texto "LEVEL ONE"
const unsigned char msg_level_one[] = { 0,1,2,1,0,6,3,4,5 };

UINT8 msg_win_x = 5;  // posición
UINT8 msg_win_y = 7;


void message_load_tiles() {
    // Carga 7 tiles a partir de MSG_TILE_BASE en el banco de patrones BG/WIN
    set_bkg_data(MSG_TILE_BASE, 7, msg_tiles);
}

// ---------------------------------------------------------
// Mostrar el texto temporalmente
// ---------------------------------------------------------
void show_level_message_window() {
    // Carga los tiles de fuente blanca
    set_win_data(0, 7, white_font_tiles);

    // Dibuja "LEVEL ONE"
    set_win_tiles(msg_win_x, msg_win_y, sizeof(msg_level_one), 1, msg_level_one);
}

// Borrar el texto (rellenar con tiles vacíos)
void hide_level_message_window() {
    UINT8 blank = 6; // tile vacío (espacio)
    fill_win_rect(msg_win_x, msg_win_y, sizeof(msg_level_one), 1, blank);
}

// Pequeño delay en frames
void wait_frames(UINT16 frames) {
    for(UINT16 i = 0; i < frames; i++) wait_vbl_done();
}
*/

/*
//const unsigned char msg_level1[] = "LEVEL ONE";

const unsigned char msg_level1[] = {
   0x16,0x0F,0x20,0x0F,0x16,0x00,0x19,0x18,0x0F
};

UINT8 msg_len = sizeof(msg_level1) - 1;
UINT8 msg_win_x = 5;
UINT8 msg_win_y = 7;
UINT8 msg_visible = 0;

// Paletas de brillo para el fade (DMG)
const UINT8 fade_steps_in[]  = { 0b11111111, 0b11110100, 0b11100100, 0b11100000 };
const UINT8 fade_steps_out[] = { 0b11100000, 0b11100100, 0b11110100, 0b11111111 };

// Ajusta este valor para la velocidad (frames por paso)
#define FADE_DELAY 10

void fade_in_text() {
    for (UINT8 i = 0; i < sizeof(fade_steps_in); i++) {
        //BGP_REG = fade_steps_in[i];
        wait_vbl_done();
        for (UINT8 f = 0; f < FADE_DELAY; f++) wait_vbl_done();
    }
}

void fade_out_text() {
    for (UINT8 i = 0; i < sizeof(fade_steps_out); i++) {
        //BGP_REG = fade_steps_out[i];
        wait_vbl_done();
        for (UINT8 f = 0; f < FADE_DELAY; f++) wait_vbl_done();
    }
}


void hide_level_message_window() {
    UINT8 blank = 0x00;
    fill_win_rect(msg_win_x, msg_win_y, msg_len, 1, blank);
    msg_visible = 0;
}

// Utilidad genérica de espera
void wait_frames(UINT16 frames) {
    for (UINT16 i = 0; i < frames; i++) wait_vbl_done();
}


void show_level_message_window() {
    font_init();
    font_set(font_load(font_min));
    

    // Inicialmente todo negro
    //BGP_REG = 0b11111111;

    //set_win_tiles(msg_win_x, msg_win_y, msg_len, 1, msg_level1);
    //SHOW_WIN;
    //msg_visible = 1;

    set_win_tiles(0, 0, msg_len, 1, msg_level1);
    move_win(80, 80);
    wait_frames(20);


    //fade_in_text();           // fundido de entrada
    //wait_frames(90);          // texto visible (~1.5 s)
    //fade_out_text();          // fundido de salida
    //hide_level_message_window();
}
*/
