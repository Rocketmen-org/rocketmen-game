#ifndef ROCKY_H
#define ROCKY_H

#include "game.h"
#include "GameObject.h"

#define TILE_W 64
#define TILE_H 64

class Rocky : public GameObject {

 public:
   Rocky(SDL_Renderer* ren);
   ~Rocky();
   bool move(coordinate_t dest);
   void attack();
   void Obj_Update();
   void Obj_Render(int x, int y);
   
   void setDone(bool done);
   bool isDone();
  
 private:

   bool done;
};

#endif
