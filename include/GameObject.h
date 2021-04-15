#ifndef GameObject_h
#define GameObject_h

#include "game.h"
#include "Sprite.h"

class GameObject{
public:
  GameObject(SDL_Renderer* ren);
  ~GameObject();

  void Obj_Init(const char* image, int f, int d, int x, int y, int frame_w, int frame_h, int w, int h);
  void Obj_Update();
  void Obj_Render(int x, int y);
  void Obj_Quit();
  int get_x_vel();
  int get_y_vel();
  int get_y_pos();
  int get_x_pos();
  int get_height();
  int get_width();
  SDL_Rect get_rect();
  void set_y_pos(int y);
  void set_x_pos(int x);
  void set_x_vel(int vel);
  void set_y_vel(int vel);
protected:
  int MAX_VEL = 5;

  int x_vel;
  int y_vel;
  
  SDL_Renderer* obj_renderer;

  Sprite* Obj_sprite;
  SDL_Texture* obj_texture;
  SDL_Rect obj_rect;
  SDL_Rect frame_rect;
};

#endif
