#include "Sprite.h"

Sprite::Sprite(){}

Sprite::~Sprite(){}

void Sprite::Sprite_init(const char* image, SDL_Renderer* ren, int f, int d, int w, int h, int s){
  game_renderer = ren;
  frames = f;
  duration = d;
  state = s; 
  sprite_rect.x = 0;
  sprite_rect.y = 0;
  sprite_rect.w = w;
  sprite_rect.h = h;
}

SDL_Rect Sprite::sprite_update(){
  
  int frame = (int) (SDL_GetTicks() / duration) % frames;

  if(state != prev_state){
    //if the state has changed since last call
    offset = frames + (-frame);
    prev_state = state;
  }
  
  frame += offset;
  frame %= frames;

  if (frame == frames - 1)
    play_until_finished = false;

  sprite_rect.x = frame * sprite_rect.w;

  sprite_rect.y = sprite_rect.h * state;  //set the y value of the frame
  return(sprite_rect);
}

void Sprite::sprite_quit(){
  //delete
}

void Sprite::set_duration(int d){
  if (!play_until_finished)
    duration = d; //sets the duration
}

void Sprite::set_state(int s){
  if (!play_until_finished)
    state = s; //sets the state
}

void Sprite::set_frames(int f){
  if (!play_until_finished)
    frames = f; //set the frames
}

void Sprite::set_play_until_finished(bool p){
  play_until_finished = p;
}
