#include "Rocky.h"   

Rocky::Rocky(SDL_Renderer* ren) : GameObject(ren){}

Rocky::~Rocky(){}
 
bool Rocky::move(coordinate_t dest){
 //convert grid coordinates to pixels
 dest.first *= TILE_W;
 dest.second *= TILE_H;
 if(obj_rect.x < dest.first){
    obj_rect.x += 2;
    //set walk right animation
    Obj_sprite->set_state(1);
    Obj_sprite->set_frames(6);
    Obj_sprite->set_duration(100);
  }
  if(obj_rect.x > dest.first){
    obj_rect.x -= 2;
    //set walk left animation
    Obj_sprite->set_state(2);
    Obj_sprite->set_frames(6);
    Obj_sprite->set_duration(100);
  }
  if(obj_rect.x == dest.first){
    if(obj_rect.y < dest.second){
      obj_rect.y += 2;
      //set walk down animation
      Obj_sprite->set_state(4);
      Obj_sprite->set_frames(6);
      Obj_sprite->set_duration(100);					
    }
    
    if(obj_rect.y > dest.second){
      obj_rect.y -= 2;
      //set walk up animation
      Obj_sprite->set_state(3);
      Obj_sprite->set_frames(6);
      Obj_sprite->set_duration(100);   
    }
  }
  if(obj_rect.x == dest.first && obj_rect.y == dest.second){
    //set sprite to Idle Animation
    //Obj_sprite->set_state(0);
    //Obj_sprite->set_frames(6);
    //Obj_sprite->set_duration(100);
    
    frame_rect = Obj_sprite->sprite_update(); //update the sprite
    return true;
  }
  
  frame_rect = Obj_sprite->sprite_update(); //update the sprite
  return false;
}

void Rocky::attack(){
  //set sprite to Attack Animation
  Obj_sprite->set_state(8);
  Obj_sprite->set_frames(6);
  Obj_sprite->set_duration(100);
  Obj_sprite->set_play_until_finished(true);
}

void Rocky::Obj_Update(){
  //set sprite to Idle Animation
  Obj_sprite->set_state(0);
  Obj_sprite->set_frames(6);
  Obj_sprite->set_duration(100);

  frame_rect = Obj_sprite->sprite_update(); //update the sprite
}

void Rocky::Obj_Render(int x, int y){
  SDL_Rect temp;
  temp.x = obj_rect.x - x;
  temp.y = obj_rect.y - y;
  temp.w = obj_rect.w;
  temp.h = obj_rect.h;
  SDL_RenderCopyEx(obj_renderer, obj_texture, &frame_rect, &temp, 0, NULL, SDL_FLIP_NONE);
}
   
void Rocky::setDone(bool d){done = d;}

bool Rocky::isDone(){return done;}

