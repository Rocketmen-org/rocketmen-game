#include "Red_Rocket.h"
#include "GameObject.h"


Red_Rocket::Red_Rocket(SDL_Renderer* ren) : GameObject(ren)
{ 
}

Red_Rocket::~Red_Rocket(){}

void Red_Rocket::Obj_Update(SDL_Rect* camera){
  if(!this->Collision(camera)){ //if the rocket goes off the screen set it to dead
    alive = false;
  }
  else if(direction == "Up"){ //move rocket up
    obj_rect.y -= 5;
  }
  else if(direction == "Down"){ //move rocket down
    obj_rect.y += 5;
  }
  else if(direction == "Left"){ //move rocket left
    obj_rect.x -= 5;
  }
  else if(direction == "Right"){ //move rocket right
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
  if(direction == "Right"){ //rotate sprite 90 to make it go right
    SDL_RenderCopyEx(obj_renderer, obj_texture, &frame_rect, &temp, 90, NULL, SDL_FLIP_NONE);
  }
  else if(direction == "Left"){ //rotate sprite 270 to make it go left

    SDL_RenderCopyEx(obj_renderer, obj_texture, &frame_rect, &temp, 270, NULL, SDL_FLIP_NONE);
  }
  else if(direction == "Up"){ //don't change sprite
     SDL_RenderCopyEx(obj_renderer, obj_texture, &frame_rect, &temp, 0, NULL, SDL_FLIP_NONE);

  }
  else if(direction == "Down"){ //flip sprite vertially
    SDL_RenderCopyEx(obj_renderer, obj_texture, &frame_rect, &temp, 0, NULL, SDL_FLIP_VERTICAL);
  }
}

void Red_Rocket::set_direction(string d){ //sets direction of rocket
  direction = d;
}

string Red_Rocket::get_direction(){ //returns direction of rocket
  return direction;
}

bool Red_Rocket::is_alive(){ //returns true if rocket is alive
  return alive;
}

void Red_Rocket::set_alive(bool a){ //sets the rocket to the bool a
  alive = a;
}

