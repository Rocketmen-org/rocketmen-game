#include "GameObject.h"
#include "player.h"
#include "GameEngine.h"

Player::Player(SDL_Renderer* ren) : GameObject(ren)
{
  x_vel = 0;
  y_vel = 0; 
}

Player::~Player(){}

void Player::Obj_Update(){
  if(State == "RUNLEFT"){ //run left state
    obj_rect.x -= 5;  //pos metophoer
    //set the sprite to running sprite
    /* Obj_sprite->set_state(1);
      Obj_sprite->set_frames(8);
      Obj_sprite->set_duration(200);
    */  
      Prev_State = State;
  }
  if(State == "RUNRIGHT"){ //run right state
    obj_rect.x += 5; //pos metophore
    //set sprite to running sprite
    /*
    Obj_sprite->set_state(1);
      Obj_sprite->set_frames(8);
      Obj_sprite->set_duration(200);
    */
      Prev_State = State;
  }
  if(State == "RUNUP"){ //run up state 
    obj_rect.y -= 5; //pos metophore
    //set sprite to running sprite
    /*  Obj_sprite->set_state(1);
    Obj_sprite->set_frames(8);
    Obj_sprite->set_duration(200);
*/
  }
  if(State == "RUNDOWN"){ //run down state
    obj_rect.y += 5; //pos metophore
    //set sprite to running sprite
    /*Obj_sprite->set_state(1);
    Obj_sprite->set_frames(8);
    Obj_sprite->set_duration(200);
    */
  }
  if(State == "IDLE"){
    //set sprite to idle sprite
    Obj_sprite->set_state(0);
    Obj_sprite->set_frames(1);
    Obj_sprite->set_duration(200);
  }

  
  //update the x and y positions of the player after the state actions have been handled
  // obj_rect.x += x_vel;
  //obj_rect.y += y_vel;
  
  if(obj_rect.x + obj_rect.w  >= LEVEL_WIDTH){
    obj_rect.x = LEVEL_WIDTH - obj_rect.w;
    x_vel = 0;
  }
  if(obj_rect.x <= 0){
    obj_rect.x = 0;
    x_vel = 0;
  }
  if(obj_rect.y <= 0){
    obj_rect.y = 0;
    y_vel = 0;
  }
  if(obj_rect.y + obj_rect.h > LEVEL_HEIGHT){
    obj_rect.y = LEVEL_HEIGHT - obj_rect.h;
    y_vel = 0;
  }
  
  frame_rect = Obj_sprite->sprite_update(); //update the player sprite
}

void Player::Obj_Render(int x, int y){
  SDL_Rect temp;
  temp.x = obj_rect.x - x;
  temp.y = obj_rect.y - y;
  temp.w = obj_rect.w;
  temp.h = obj_rect.h;
  if(State == "RUNLEFT"){ //if running left flip the render
    SDL_RenderCopyEx(obj_renderer, obj_texture, &frame_rect, &temp, 0, NULL, SDL_FLIP_HORIZONTAL);
  }
  else if((State == "IDLE" || State == "RUNUP" || State == "RUNDOWN") && Prev_State == "RUNLEFT"){
    //if switches to idle or jump from left keep the flip
    SDL_RenderCopyEx(obj_renderer, obj_texture, &frame_rect, &temp, 0, NULL, SDL_FLIP_HORIZONTAL);
  }
  else{ //render normally
    SDL_RenderCopyEx(obj_renderer, obj_texture, &frame_rect, &temp, 0, NULL, SDL_FLIP_NONE);
  }
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
  return is_jumping; //returns true if the player is mid jump
}

string Player::get_prev_state(){
  return Prev_State;
}
