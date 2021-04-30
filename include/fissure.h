#ifndef FISSURE_H
#define FISSURE_H

#include "game.h"
#include "GameObject.h"

class Fissure : public GameObject {

 public:
   Fissure(SDL_Renderer* ren);
   ~Fissure();
   void Obj_Update();
   void Obj_Render(int x, int y);

   void setLifetime(int l);
  
 private:
   int lifetime;
   bool alive;
};

#endif
