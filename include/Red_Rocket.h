#ifndef RED_ROCKET_H
#define RED_ROCKET_H

#include "GameObject.h"
#include "game.h"

class Red_Rocket : public GameObject {
 public:
  Red_Rocket(SDL_Renderer* ren);
  ~Red_Rocket();
  void Obj_Update(SDL_Rect* player, string direction);
  bool Collision(SDL_Rect* other); 
  void Obj_Render(int x, int y);
  bool get_is_flipped();
 private:
};

#endif
