#include "Tiles.h"
#include "GameEngine.h"

Tile::Tile(SDL_Renderer* ren) : GameObject(ren){
  
}

Tile::~Tile(){
}

void Tile::Obj_Init(int x, int y, int TileType){
  SDL_Surface* hold = IMG_Load(tile_set);
  obj_texture = SDL_CreateTextureFromSurface(obj_renderer, hold);
  SDL_FreeSurface(hold);

  obj_rect.x = x;
  obj_rect.y = y;
  obj_rect.w = TILE_WIDTH;
  obj_rect.h = TILE_HEIGHT;

  frame_rect.w = TILE_WIDTH;
  frame_rect.h = TILE_HEIGHT;
  //set what frame corrisponds to the tile type passed in
  if(TileType == 00){
    frame_rect.x = 0 * TILE_WIDTH;
    frame_rect.y = 1 * TILE_HEIGHT;
  }
  else if(TileType == 01){
    frame_rect.x = 1 * TILE_WIDTH;
    frame_rect.y = 1 * TILE_HEIGHT;
  }
  else if(TileType == 02){
    frame_rect.x = 2 * TILE_WIDTH;
    frame_rect.y = 1 * TILE_HEIGHT;
  }
  else if(TileType == 03){
    frame_rect.x = 5 * TILE_WIDTH;
    frame_rect.y = 0 * TILE_HEIGHT;
  }
  else if(TileType == 04){
    frame_rect.x = 6 * TILE_WIDTH;
    frame_rect.y = 0 * TILE_HEIGHT;
  }
  else if(TileType == 05){
    frame_rect.x = 2 * TILE_WIDTH;
    frame_rect.y = 2 * TILE_HEIGHT;
  }
  else{
    frame_rect.x = 0;
    frame_rect.y = 0;
  }
}

void Tile::Obj_Render(SDL_Rect Cam){
  //check if the tile is inside the camera and render it if it is
  if( (obj_rect.x >= (Cam.x - TILE_WIDTH)) && (obj_rect.x <= (Cam.x + Cam.w + TILE_WIDTH)) ){
    if( (obj_rect.y >= (Cam.y - TILE_WIDTH)) && (obj_rect.y <= (Cam.y + Cam.h + TILE_HEIGHT)) ){
      SDL_Rect temp;
      temp.x = obj_rect.x - Cam.x;
      temp.y = obj_rect.y - Cam.y;
      temp.w = obj_rect.w;
      temp.h = obj_rect.h;
      SDL_RenderCopy(obj_renderer, obj_texture, &frame_rect, &temp);
    }
  }
}

int Tile::get_type(){
  return tile_type; //returns the tile type
}

SDL_Rect Tile::getTile(){
  return obj_rect; //returns the rectangle where the tile is to be displayed
}
