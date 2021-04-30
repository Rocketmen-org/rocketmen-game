#ifndef SPRITE_H
#define SPRITE_H

#include "game.h"

class Sprite {
 public:
  Sprite();
  ~Sprite();
  void Sprite_init(const char* image, SDL_Renderer* ren, int f, int d, int w, int h, int s);
  SDL_Rect sprite_update();
  void sprite_render(SDL_Renderer* ren);
  void sprite_quit();
  void set_duration(int d);
  void set_state(int s);
  void set_frames(int f);
  void set_play_until_finished(bool p);

 private:
  //SDL_Texture* sprite_image;
  SDL_Rect sprite_rect;
  
  int frames = 0;
  int prev_state = -1;
  
  int duration;
  int state;
  int offset;
  bool play_until_finished;

  SDL_Renderer* game_renderer;
};

#endif
