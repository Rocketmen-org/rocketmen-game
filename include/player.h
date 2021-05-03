#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "game.h"

class Player : public GameObject {
 public:
  Player(SDL_Renderer* ren);
  ~Player();
  void set_state(string A);
  void set_prev_state(string A);
  void set_sprite(string A);
  string get_state();
  void Obj_Update(int Rect_x, int Rect_y);
  void Obj_Render(int x, int y);
 private:
  string State;
  string Shoot_direction;
};

#endif
