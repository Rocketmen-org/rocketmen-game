#ifndef RockyManager_h
#define RockyManager_h

#include <vector>

#include "game.h"
#include "Sprite.h"
#include "Rocky.h"

#define NUM_ROCKYS 1
#define ROCKY_START_X 4 * 64
#define ROCKY_START_Y 4 * 64

class RockyManager{
	
public:
  RockyManager(SDL_Renderer* ren);
  ~RockyManager();

  void init(const char* image);
  void update();
  void render(int x, int y);
  void quit();

  bool turnOver();
  bool defend();
  void setAttack(int x, int y);
  void setDefend();

  SDL_Rect getRect();
  void kill();

private:
  
  SDL_Renderer* obj_renderer;

  vector<Rocky*> rockys;
  vector<struct coordinate> dest;

  bool attack;
  bool turn_over;
  bool alive;
};


#endif