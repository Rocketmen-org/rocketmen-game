#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "game.h"

class Background{
 public:
  Background(SDL_Renderer* ren);
  ~Background();
  void BG_Init(const char* image, int y, int width, int height, int w, int h, int lay);
  void BG_Update(string state, int player_x_pos);
  void BG_Render();
  
private:
  SDL_Texture* BG_image;
  SDL_Rect BG_rect;
  SDL_Rect Window;

  int image_width;
  int image_height;
  int layer;
  
  SDL_Renderer* game_renderer;
};

#endif
