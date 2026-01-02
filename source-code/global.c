#include "global.h"
#include <gb/gb.h>


void clear_bkg_screen() {
    DISPLAY_OFF; 
    HIDE_BKG; 

    // Tile 0 debe ser tu tile “en blanco”
    fill_bkg_rect(0, 0, 32, 32, 0);

    SCX_REG = 0;
    SCY_REG = 0;

    SHOW_BKG;
    DISPLAY_ON;
}



void performantGeneralDelay(UINT8 numloop) {
   UINT8 ii;
   for(ii=0; ii<numloop; ii++){
      wait_vbl_done();
   }
}

//FADEOUT
void fadeout(){
   for(int i=0;i<4;i++){
      switch(i){
         case 0:
             BGP_REG = 0xE4;
             break;
         case 1:
             BGP_REG = 0xF9;
             break;
         case 2:
             BGP_REG = 0xFE;
             break;
         case 3:
             BGP_REG = 0xFF;
             break;
      }
      performantGeneralDelay(10);

   }
}

//FADEIN
void fadein(){
   for(int i=0;i<3;i++){
      switch(i){
         case 0:
             BGP_REG = 0xFE;
             break;
         case 1:
             BGP_REG = 0xF9;
             break;
         case 2:
             BGP_REG = 0xE4;
             break;
      }
      performantGeneralDelay(10);
   }
}