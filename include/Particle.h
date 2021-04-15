#ifndef PARTICLE_H
#define PARTICLE_H

#include "game.h"

class Particle{
 public:
  Particle();

  void obj_init(const char* graphic, SDL_Renderer* ren, int X, int Y, int W, int H);
  
  void Update_FireWork();
  void Draw_FireWork(SDL_Renderer* ren);

  void destroy();


  void set_x_vel(int vel);
  void set_y_vel(int vel);
  void set_lifetime(int life);
  
 private:
  
  SDL_Texture* obj_graphic;
  SDL_Rect obj_rect;
  
  int x_vel, y_vel;

  int lifetime;

  SDL_Renderer* obj_renderer;
};

#endif
