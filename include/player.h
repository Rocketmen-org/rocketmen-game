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
  string get_prev_state();
  bool get_is_jumping();
  void Obj_Update(int Rect_x, int Rect_y);
  void Obj_Render(int x, int y);
  bool get_is_flipped();
 private:
  string State;
  string Prev_State;
  int count = 0;
  //int y_prev_pos;
};

#endif
