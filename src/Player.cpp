#include "GameObject.h"
#include "player.h"
#include "GameEngine.h"

Player::Player(SDL_Renderer* ren) : GameObject(ren)
{
  x_vel = 0;
  y_vel = 0; 
}

Player::~Player(){}

void Player::Obj_Update(int Rect_x, int Rect_y){
  if(obj_rect.x < Rect_x){
    obj_rect.x += 2;
    //set walk right animation
    Obj_sprite->set_state(1);
    Obj_sprite->set_frames(6);
    Obj_sprite->set_duration(200);
  }
  if(obj_rect.x > Rect_x){
    obj_rect.x -= 2;
    //set walk left animation
    Obj_sprite->set_state(2);
    Obj_sprite->set_frames(6);
    Obj_sprite->set_duration(200);
  }
  if(obj_rect.x == Rect_x){
    if(obj_rect.y < Rect_y){
      obj_rect.y += 2;
      //set walk down animation
      Obj_sprite->set_state(4);
      Obj_sprite->set_frames(6);
      Obj_sprite->set_duration(200);					
    }
    
    if(obj_rect.y > Rect_y){
      obj_rect.y -= 2;
      //set walk up animation
      Obj_sprite->set_state(3);
      Obj_sprite->set_frames(6);
      Obj_sprite->set_duration(200);   
    }
  }
  if(obj_rect.x == Rect_x && obj_rect.y == Rect_y){
    //set sprite to Idle Animation
    Obj_sprite->set_state(0);
    Obj_sprite->set_frames(6);
    Obj_sprite->set_duration(200);
  }
  
  frame_rect = Obj_sprite->sprite_update(); //update the player sprite
}

void Player::Obj_Render(int x, int y){
  SDL_Rect temp;
  temp.x = obj_rect.x - x;
  temp.y = obj_rect.y - y;
  temp.w = obj_rect.w;
  temp.h = obj_rect.h;
  SDL_RenderCopyEx(obj_renderer, obj_texture, &frame_rect, &temp, 0, NULL, SDL_FLIP_NONE);
}

void Player::set_state(string A){
  State = A; //sets the state so that it can be changed by the key presses
}

string Player::get_state(){
  return State;  //returns state
}

void Player::set_prev_state(string A){
  Prev_State = A; //store previous state before jumping so that we can return to it
}

bool Player::get_is_jumping(){
  return true;
}

string Player::get_prev_state(){
  return Prev_State;
}

void Player::set_sprite(string A){
  if(A == "Right"){
    std::cout << "enter shoot" << std::endl;
    Obj_sprite->set_state(5);
    Obj_sprite->set_frames(6);
    Obj_sprite->set_duration(200);
  }
  else if(A == "Left"){
    Obj_sprite->set_state(6);
    Obj_sprite->set_frames(6);
    Obj_sprite->set_duration(200);
  }
  else if(A == "Up"){
    Obj_sprite->set_state(7);
    Obj_sprite->set_frames(6);
    Obj_sprite->set_duration(200);
  }
  else if(A == "Up"){
    Obj_sprite->set_state(8);
    Obj_sprite->set_frames(6);
    Obj_sprite->set_duration(200);
  }
  /*else if(A == "Idle"){
    Obj_sprite->set_state(0);
    Obj_sprite->set_frames(6);
    Obj_sprite->set_duration(200);
    }*/
}

