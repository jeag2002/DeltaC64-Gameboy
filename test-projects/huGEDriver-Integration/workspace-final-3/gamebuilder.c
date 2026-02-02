#include "gamebuilder.h"

#include <stdio.h>
#include <gb/font.h>
#include <rand.h>

#include "level_1.h"
#include "level_1_tiles_2.h"
#include "global.h"
#include "Sprites.h"
#include "background.h"
#include "captions.h"
#include "world.h"


INT16 scroll_x = -1;

unsigned char hud_line[20] = {
    0x1D,0x0D,0x19,0x1C,0x0F,       // SCORE
    0x00,0x00,0x00,0x00,            // NUMBER
    0x00,0x00,0x00,                 // SHOOT
    0x16,0x13,0x20,0x0F,            // LIVE
    0x00,0x00,0x00                  // NUMBER
};

font_t min_font;
unsigned char *background_map;


//CONVERSION VALUES FOR HUD
void numberToTiles(UINT16 value, unsigned char* dest, UINT8 digits) {
    for (INT8 i = digits - 1; i >= 0; i--) {
        dest[i] = (value % 10) + 1;
        value /= 10;
    }
}

//SET TEXT HUD
void setHUD(UINT8 score, UINT8 shoot, UINT8 lives) {
  numberToTiles(score, &hud_line[5], 4);
  numberToTiles(lives, &hud_line[16], 3);
  if (shoot == TYPE_SHOOT_PLAYER_ONE) {
     hud_line[10] = 0x02;
  } else if (shoot == TYPE_SHOOT_PLAYER_TWO) {
     hud_line[10] = 0x03;
  } else if (shoot == TYPE_SHOOT_PLAYER_THREE) {
     hud_line[10] = 0x04;
  } else {
     hud_line[10] = 0x1D;
  }
  set_win_tiles(0, 0, 20, 1, hud_line);
}


//DELAY
void performantDelay(UINT8 numloops) {
  UINT8 i;
  for(i=0; i<numloops; i++) {
    wait_vbl_done();
  }  
}

//INC WORLD SCROLL
void incWorldScroll() {
    scroll_x++;
}

//GET WORLD SCROLL
INT16 getWorldScroll() {
    return scroll_x;
}

//LAUNCH ENVIRONMENT
void launchLevel(int level) {
    DISPLAY_OFF;

    HIDE_BKG;
    HIDE_WIN;
    HIDE_SPRITES;
    SPRITES_8x8;

    UINT8 OLD = _current_bank;

    //BACKGROUND 
    //SWITCH_ROM(BANK(tile_background_map));
    SWITCH_ROM(5);
    set_bkg_data(0, 123, tile_background_map);

    //SPRITES
    //NOTE: WE'RE WORKING WITH THE DMG-01 VERSION. ONLY 1 BANK, MAX 92 SPRITES.
    SWITCH_ROM(3);
    set_sprite_data(0, 92, sprites_videogame);

    SWITCH_ROM(OLD);

    //HUD
    /////////////////////////////////////////////////
    font_init();
    min_font = font_load(font_min);
    font_set(min_font);


    setHUD(0,TYPE_SHOOT_PLAYER_ONE,0);
    move_win(7,135);
    //////////////////////////////////////////////////
 
    scroll_x = -1;
          
    SHOW_BKG;
    SHOW_SPRITES;
    SHOW_WIN;
    DISPLAY_ON; 

    //set background map
    background_map = getLevelFromIndex(level);

    //BACKGROUND MAP WILL CHANGE X LEVEL.
    //set_bkg_submap(0, 0, SCREEN_WIDTH_TILE, SCREEN_HEIGHT_TILE, background_map_levelone, MAP_WIDTH_TILE);
    set_bkg_submap(0, 0, SCREEN_WIDTH_TILE, SCREEN_HEIGHT_TILE, background_map, MAP_WIDTH_TILE);
    
    //PARALLAX 
    init_background(level);

    //LAUNCH LEVEL MESSAGE
    show_level_one_msg();
    wait_frames_level_one(30);
    hide_msg();
    //END LEVEL MESSAGE
}

//MOVE BACKGROUND ONE STEP
BYTE stepLevel() {

    BYTE DONE = 0;

    //scroll_x++;

    //MOVE WINDOW ONE TILE TO RIGHT
    if(scroll_x % 8 == 0) {
       wait_vbl_done();
       UINT16 tile_col = (scroll_x / 8) + SCREEN_WIDTH_TILE; 
       if(tile_col < MAP_WIDTH_TILE) {
           set_bkg_submap(tile_col, 0, 1, SCREEN_HEIGHT_TILE, background_map, MAP_WIDTH_TILE);
        }
    }

    process_background(scroll_x);
    move_bkg(scroll_x,0);

    if(scroll_x >= (MAP_WIDTH_TILE - SCREEN_WIDTH_TILE) * 8) {
        DONE = 1;
        show_level_end_msg();
        wait_frames_level_one(30);
        hide_msg();
    }

    return DONE;
}
