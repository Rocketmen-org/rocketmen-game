#ifndef TILES_H
#define TILES_H

#include "GameObject.h"
#include "game.h"

class Tile : public GameObject {
 public:
  Tile(SDL_Renderer* ren);
  ~Tile();
  void Obj_Init(int x, int y, int TileType);
  void Obj_Render(SDL_Rect Cam);

  int get_type();

  SDL_Rect getTile();
 
 private:
  int tile_type;

  const char* tile_set = "images/Tileset_trans.png";
  
};

#endif
