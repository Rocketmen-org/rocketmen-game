#include "Red_Rocket.h"

Red_Rocket::Red_Rocket(SDL_Renderer* ren) : GameObject(ren)
{ 
}

Red_Rocket::~Red_Rocket(){}


void Red_Rocket::Obj_Update(SDL_Rect* Camera){
  if(!this->Collision(Camera)){
    alive = false;
  }
  else if(direction == "Up"){
    obj_rect.y -= 5;
  }
  else if(direction == "Down"){
    obj_rect.y += 5;
  }
  else if(direction == "Left"){
    obj_rect.x -= 5;
  }
  else if(direction == "Right"){
    obj_rect.x += 5;
  }
}

bool Red_Rocket::Collision(SDL_Rect* b){
   //create one box
  int Left_A = obj_rect.x + 40;
  int Right_A = Left_A + obj_rect.w - 40;
  int Top_A = obj_rect.y;
  int Bottom_A = Top_A + obj_rect.h;
  //create another box
  int Left_B = b->x;
  int Right_B = Left_B + b->w;
  int Top_B = b->y;
  int Bottom_B = Top_B + b->h;

  //this checks if y locations arent overlapping
  if(Bottom_A <= Top_B){
    return false;
  }
  if(Top_A >= Bottom_B){
    return false;
  }
  //these check check if x locations arent overlapping
  if(Right_A <= Left_B){
    return false;
  }
  if(Left_A >= Right_B){
    return false;
  }
  //if none of the not overlapping conditions is met then it is overlapping
  return true;
}

void Red_Rocket::Obj_Render(int x, int y){
  SDL_Rect temp;
  temp.x = obj_rect.x - x;
  temp.y = obj_rect.y - y;
  temp.w = obj_rect.w;
  temp.h = obj_rect.h;
  if(direction == "Right"){
    SDL_RenderCopyEx(obj_renderer, obj_texture, &frame_rect, &temp, 90, NULL, SDL_FLIP_NONE);
  }
  else if(direction == "Left"){
    SDL_RenderCopyEx(obj_renderer, obj_texture, &frame_rect, &temp, 270, NULL, SDL_FLIP_NONE);
  }
  else if(direction == "Up"){
     SDL_RenderCopyEx(obj_renderer, obj_texture, &frame_rect, &temp, 0, NULL, SDL_FLIP_HORIZONTAL);
  }
  else if(direction == "Down"){
    SDL_RenderCopyEx(obj_renderer, obj_texture, &frame_rect, &temp, 0, NULL, SDL_FLIP_VERTICAL);
  }
}

void Red_Rocket::set_direction(string d){
  direction = d;
}

string Red_Rocket::get_direction(){
  return direction;
}

bool Red_Rocket::is_alive(){
  return alive;
}

void Red_Rocket::set_alive(bool a){
  alive = a;
}
