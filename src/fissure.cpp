#include "fissure.h"

Fissure::Fissure(SDL_Renderer* ren) : GameObject(ren){}

Fissure::~Fissure(){}

void Fissure::Obj_Update(){
  if (lifetime <= 0)
    alive = false;
  lifetime --;
}

void Fissure::Obj_Render(int x, int y){
  if (alive){
    SDL_Rect temp;
    temp.x = obj_rect.x - x;
    temp.y = obj_rect.y - y;
    temp.w = obj_rect.w;
    temp.h = obj_rect.h;
    SDL_RenderCopyEx(obj_renderer, obj_texture, &frame_rect, &temp, 0, NULL, SDL_FLIP_NONE);
  }
}

void Fissure::setLifetime(int l){
  lifetime = l;
}
