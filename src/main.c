#include <stdio.h>
#include <gb/gb.h>

#include "assets/sprites/PinHeads.h"

int main(void){
  printf("\n\tPINHEADS\n\tPRESENTS:");
  UINT8 currentspriteindex = 0;

  set_sprite_data(0,2, PinHeads);
  set_sprite_tile(0,0);
  set_sprite_tile(1,1);

  move_sprite(0, 88, 78);
  move_sprite(1, 80, 78);
  SHOW_SPRITES;

  for(;;){
    currentspriteindex ^= 1;
    set_sprite_tile(0,currentspriteindex);
    set_sprite_tile(1,currentspriteindex ^ 1);
    delay(1000);
  }

  return 0;
}
