#include <stdio.h>
#include <gb/gb.h>

#include "assets/sprites/PinHeads.h"

#define PINHEAD_LARRY 0
#define PINHEAD_MOE   1
#define CURSOR_SPRITE 2
#define CURSOR_ANIM_LEN 32

int cursor_example(void){
  set_sprite_data(0,4,PinHeads);
  set_sprite_tile(PINHEAD_LARRY,0);
  set_sprite_tile(PINHEAD_MOE,1);
  set_sprite_tile(CURSOR_SPRITE,2); //3 and 4 for animation

  uint8_t larry_x = 80;
  uint8_t moe_x = 88;
  const uint8_t items_y = 78;

  move_sprite(PINHEAD_LARRY, larry_x, items_y); //Statically Draw Larry and Moe
  move_sprite(PINHEAD_MOE, moe_x, items_y);

  uint8_t selection[] = {larry_x, moe_x};
  uint8_t selection_idx = 0;

  SHOW_SPRITES;

  uint8_t anim_tick = CURSOR_ANIM_LEN;
  uint8_t anim_idx = 0;

  for(;;){
    move_sprite(CURSOR_SPRITE, selection[selection_idx], items_y); //Draw Cursor

    vsync();
    uint8_t joy = joypad();
    if(joy & J_LEFT){ //&& selection_idx == 1){
      selection_idx = 0;
    }else if(joy & J_RIGHT){// && selection_idx == 0){
      selection_idx = 1;
    }

    if(anim_tick == 0){
      anim_idx ^= 1;
      set_sprite_tile(CURSOR_SPRITE, 2 + anim_idx);
      anim_tick = CURSOR_ANIM_LEN;
    }
    --anim_tick;
  }

}

int main(void){
  //TODO abstract over battlestate scene
  cursor_example();
  return 0;
}
