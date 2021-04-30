#ifndef ROCKY_H
#define ROCKY_H

#include "game.h"
#include "GameObject.h"

struct coordinate{
  int x;
  int y;
};

class Rocky : public GameObject {

 public:
   Rocky(SDL_Renderer* ren);
   ~Rocky();
   bool move(struct coordinate dest);
   void attack();
   void Obj_Update();
   void Obj_Render(int x, int y);
   
   void setDone(bool done);
   bool isDone();
  
 private:
   bool done;
};

#endif
