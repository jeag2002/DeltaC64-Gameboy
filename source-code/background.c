/** 
 * BACKGROUND PARALLAX
 * 
*/

#include "background.h"

#include <gb/gb.h>
#include <rand.h>
#include "level_1.h"
#include "world.h"


#define TILE_BLACK   240
#define TILE_STAR1   241  // pequeño tenue
#define TILE_STAR2   242  // pequeño medio
#define TILE_STAR3   243  // pequeño brillante
#define TILE_STAR4   244  // grande tenue
#define TILE_STAR5   245  // grande medio
#define STAR_COUNT   6    // cantidad total de variantes
#define NUM_STARS    8

unsigned char *background_map_1;

const unsigned char sky_tiles[] = {
    // --- TILE 240: negro ---
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,

    // --- TILE 241: pequeña tenue (un punto) ---
    0xFF,0xFF,0xFF,0xE7,0xE7,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,

    // --- TILE 242: pequeña media (dos puntos) ---
    0xFF,0xFF,0xE7,0xC3,0xC3,0xE7,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,

    // --- TILE 243: pequeña brillante (cruz) ---
    0xFF,0xFF,0xE7,0x81,0x81,0xE7,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,

    // --- TILE 244: grande tenue (zona más ancha) ---
    0xFF,0xFF,0xE7,0xE7,0xE7,0xE7,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,

    // --- TILE 245: grande media ---
    0xFF,0xEF,0xEF,0xC3,0xC3,0xEF,0xEF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
};

typedef struct {
    //situación mundo
    UINT16 x_world;
    
    //situación pantalla
    UINT16 x_screen;

    //situación vram
    UINT16 y;

    BYTE hide;
    BYTE up;
    UINT8 sprite_id;
    UINT8 speed;
} Star;
Star stars[NUM_STARS];



void set_tile_background(UINT16 x_world, UINT16 y, UINT8 sprite_id) {

    UINT16 vram_x = (x_world >> 3) & 31;
    UINT16 vram_y = (y >> 3) & 31;

    set_bkg_tiles(vram_x, vram_y, 1, 1, &sprite_id);
}


UINT8 obtain_tile_background(UINT16 x_world, UINT16 y) {

    UINT16 x_tile = (x_world >> 3);
    UINT16 y_tile = (y >> 3);

    //UINT8 tile = background_map_levelone[x_tile + y_tile * MAP_WIDTH_TILE];
    UINT8 tile = background_map_1[x_tile + y_tile * MAP_WIDTH_TILE];
    return tile;
}


void reinit_starfield(Star *starts, UINT16 scroll_x) {

    starts->x_screen = rand() % ((SCREEN_WIDTH - 2) - (SCREEN_WIDTH - 10)) + (SCREEN_WIDTH - 10);
    starts->x_world = starts->x_screen + scroll_x;
    starts->y = rand() % ((SCREEN_HEIGHT - 15) - 16) + 16;

    UINT8 map_tile = obtain_tile_background(starts->x_world, starts->y);
    if (map_tile == 0x7A) {
        starts->hide = FALSE;
        starts->sprite_id = TILE_STAR1;
        UINT8 sprite_id = starts->sprite_id;
        set_tile_background(starts->x_world, starts->y, sprite_id);
    } else {
        starts->hide = TRUE;
    }

    starts->sprite_id++;
    starts->speed = 1 + rand() % (3);
    starts->up = TRUE;
}

void delete_startfield(Star *starts) {
    starts->x_world = 0;  
    starts->x_screen = 0;
    starts->y = 0;
    starts->speed = 0;
    starts->up = TRUE;
    starts->hide = FALSE;
    starts->sprite_id = TILE_BLACK;
}



/**
 * @brief Process current start
 * 
 * @param starts 
 * @param scroll_x 
 */

void process_startfield(Star *starts, UINT16 scroll_x) {
    
    if (starts->hide == FALSE) {
        set_tile_background(starts->x_world, starts->y, TILE_BLACK);
    }

    int x_screen_moving = starts->x_screen - starts->speed;

    if (x_screen_moving > 0) {
        
        int x_world = x_screen_moving + scroll_x;

        UINT8 map_tile = obtain_tile_background(x_world, starts->y);
        if (map_tile == 0x7A) {
            starts->hide = FALSE;
            set_tile_background(x_world, starts->y, starts->sprite_id);
        } else {
            starts->hide = TRUE;
        }
    
        //NEXT STEP ANIMATION
        if (starts->up == TRUE) {
            starts->sprite_id = starts->sprite_id + 1;
            if ((starts->sprite_id > TILE_STAR5)) {
                starts->sprite_id = starts->sprite_id - 1;
                starts->up = FALSE;
            }
        } else {
            starts->sprite_id = starts->sprite_id - 1;
            if ((starts->sprite_id < TILE_STAR1)) {
                starts->sprite_id = starts->sprite_id + 1;
                starts->up = TRUE;
            }
        }

        starts->x_screen = x_screen_moving;
        starts->x_world = x_world;

    } else {
        set_tile_background(0, starts->y, TILE_BLACK);
        delete_startfield(starts);
        reinit_starfield(starts, scroll_x);
    }
}




void init_first_startfield(Star *starts) {
    starts->x_screen = rand() % ((SCREEN_WIDTH - 7) - 8) + 8;
    starts->x_world = starts->x_screen;
    starts->y = rand() % ((SCREEN_HEIGHT - 15) - 16) + 16;

    starts->sprite_id =  TILE_STAR1; // pequeña
    starts->up = TRUE;
    starts->speed = 1 + rand() % (3);

    UINT8 map_tile = obtain_tile_background(starts->x_world, starts->y);
    if (map_tile == 0x7A) {
        starts->hide = FALSE;
        UINT8 sprite_id = starts->sprite_id;
        set_tile_background(starts->x_world, starts->y, sprite_id);
    } else {
        starts->hide = TRUE;
    }

    starts->sprite_id++;
}



/**
 * INIT_TILE_MAP FIRST PLACE
 *  @brief 
 */
void init_background(int level) {
    initrand(DIV_REG);
    // LOAD STARTS IN THE BACKGROUND TILEMAP
    set_bkg_data(TILE_BLACK, STAR_COUNT, sky_tiles);    

    background_map_1 = getLevelFromIndex(level);

    for(UINT8 i=0; i<NUM_STARS; i++) {
        init_first_startfield(&stars[i]);
    }

    
}


void process_background(UINT16 scroll) {
    for(UINT8 i=0; i<NUM_STARS; i++) {
        process_startfield(&stars[i], scroll);
    }
}
