#include <stdio.h>
#include <gb/gb.h>

#include "assets/sprites/PinHeads.h"

#define SPRITE_PINHEAD_LARRY_INDEX 0
#define SPRITE_PINHEAD_MOE_INDEX   1
#define SPRITE_CURSOR_INDEX  2 //3 is occupied by small

#define CURSOR_ANIM_LEN 32

void init_setupSprites(void){
  set_sprite_data(0,4,PinHeads);
  set_sprite_tile(SPRITE_PINHEAD_LARRY_INDEX,0);
  set_sprite_tile(SPRITE_PINHEAD_MOE_INDEX,1);
  set_sprite_tile(SPRITE_CURSOR_INDEX, 2); //2 and 3 for animation
}

typedef struct screen_entity {
  //TODO CURSOR SIZE FOR BIG BODY EXAMPLE
  uint8_t sprite_index;
  uint8_t screen_x;
  uint8_t screen_y;
} screen_entity;

void draw_game_entities(screen_entity *es, uint8_t es_len){
  for(uint8_t i = 0; i < es_len; i++){
    move_sprite(es[i].sprite_index, es[i].screen_x, es[i].screen_y);
  }
}

typedef struct screen_cursor {
  screen_entity * selectables;  //CHANGES TO GAMESTATE SELECTABLES REQUIRE THE CURSOR TO BE REBUILT
  uint8_t selectables_len;
  uint8_t selection_idx;        //MUTABLE BY INPUT HANDLER
  uint8_t sprite_index;

  uint8_t anim_tick;
  uint8_t anim_idx;
} screen_cursor;

void draw_screen_cursor(screen_cursor * c){
    move_sprite(c->sprite_index
        , c->selectables[c->selection_idx].screen_x
        , c->selectables[c->selection_idx].screen_y);
}
void cursor_input_handler(screen_cursor *c, uint8_t joy){
    //TODO INC AND LIMIT FOR N SELECTABLE ENTITIES
    if(joy & J_LEFT){
      c->selection_idx = 0;
    }else if(joy & J_RIGHT){
      c->selection_idx = 1;
    }

}

void cursor_animation_handler(screen_cursor * c){
    if(c->anim_tick == 0){
      c->anim_idx ^= 1;
      set_sprite_tile(c->sprite_index, c->sprite_index + c->anim_idx);
      c->anim_tick = CURSOR_ANIM_LEN;
    }
    --c->anim_tick;
}

//Abstract over scene entity sprites
int cursor_example(void){
  init_setupSprites();

  screen_entity game_entities[] = {                       //TODO make this references to gamestate entities?
    { SPRITE_PINHEAD_LARRY_INDEX, 80, 78 }
   ,{ SPRITE_PINHEAD_MOE_INDEX, 88, 78}
  };
  const uint8_t game_entities_len = 2;

  screen_cursor cursor = {{ &game_entities[0], &game_entities[1] }, 2, 0, SPRITE_CURSOR_INDEX, CURSOR_ANIM_LEN, 0 };

  SHOW_SPRITES;

  for(;;){
    draw_game_entities(game_entities, game_entities_len);
    draw_screen_cursor(&cursor);

    vsync();

    uint8_t joy = joypad();                               //TODO EXAMPLE PRESS A AND UI POPS UP, INSTALLS DIFFERENT INPUT HANDLER.
    cursor_input_handler(&cursor, joy);
    cursor_animation_handler(&cursor);
  }

}

int main(void){
  //TODO abstract over battlestate scene
  cursor_example();
  return 0;
}
