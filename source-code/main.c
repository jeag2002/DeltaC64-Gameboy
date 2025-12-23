#include <gb/gb.h>
#include <stdio.h>

#include "splash.h"
#include "game.h"

//DELAY
void performantdelay(UINT8 numloop) {
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
      performantdelay(10);

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
      performantdelay(10);
   }
}


//MAIN
void main(){
   processSplash();
   fadeout();  
   fadein(); 
   run();
}