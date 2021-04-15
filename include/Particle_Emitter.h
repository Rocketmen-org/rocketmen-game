#ifndef PARTICLE_EMITTER_H
#define PARTICLE_EMITTER_H

#include "game.h"
#include "Particle.h"

const int MAX_PARTS = 100;

class Particle_Emitter{
  
public:
  Particle_Emitter();
  ~Particle_Emitter();
  void PE_Init(const char* graphic, SDL_Renderer* ren, int X, int Y, int W, int H, int type);

  void Update();
  void draw(SDL_Renderer* ren);

  void quit();

private:
  Particle* particles[MAX_PARTS];
  
  int x_pos;
  int y_pos;
  int part_type;
};
  
#endif
