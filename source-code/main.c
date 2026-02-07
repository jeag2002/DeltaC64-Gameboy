#include <gb/gb.h>
#include <stdio.h>

#include "splash.h"
#include "game.h"
#include "global.h"


//MAIN
void main(){
   while(TRUE) {
      clear_bkg_screen();
      processSplash();
      run(); 
   }
}



