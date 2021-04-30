#ifndef RED_ROCKET_H
#define RED_ROCKET_H

#include "GameObject.h"
#include "game.h"

class Red_Rocket : public GameObject {
 public:
  Red_Rocket(SDL_Renderer* ren);
  ~Red_Rocket();
  void Obj_Update(SDL_Rect* player);
  bool Collision(SDL_Rect* other); 
  void Obj_Render(int x, int y);
  void set_direction(string d);
  string get_direction();
  bool is_alive();
  void set_alive(bool a);
private:
  string direction;
  bool alive;
};

#endif
