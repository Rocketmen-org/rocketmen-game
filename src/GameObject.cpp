#include "GameObject.h"

GameObject::GameObject(SDL_Renderer* ren){
  obj_renderer = ren;
}

GameObject::~GameObject(){
}

void GameObject::Obj_Init(const char* image, int f, int d, int x, int y, int frame_w, int frame_h, int w, int h, int alpha){
  //initalize the object image and location
  SDL_Surface* hold = IMG_Load(image);
  obj_texture = SDL_CreateTextureFromSurface(obj_renderer, hold);
  SDL_FreeSurface(hold);
  
  SDL_SetTextureAlphaMod(obj_texture, alpha);
  
  obj_rect.x = x;
  obj_rect.y = y;
  obj_rect.w = w;
  obj_rect.h = h;

  frame_rect.x = 0;
  frame_rect.y = 0;
  frame_rect.w = frame_w;
  frame_rect.h = frame_h;
  
  //create the sprite to represent the object
  Obj_sprite = new Sprite();
  Obj_sprite->Sprite_init(image, obj_renderer, f, d, frame_w, frame_h, 0);
}

void GameObject::Obj_Update(){
  frame_rect = Obj_sprite->sprite_update(); //update the frame that is to be displayed
}

void GameObject::Obj_Render(int x, int y){
  //renderer the object based on camera location
  SDL_Rect temp;
  temp.x = obj_rect.x - x;
  temp.y = obj_rect.y - y;
  temp.w = obj_rect.w;
  temp.h = obj_rect.h;
 
  SDL_RenderCopy(obj_renderer, obj_texture, &frame_rect, &temp);
}

void GameObject::Obj_Quit(){
  //Destroy Objects
}

int GameObject::get_y_pos(){
  return obj_rect.y; //returns y position of object
}

int GameObject::get_x_pos(){
  return obj_rect.x; //returns x position of object
}

void GameObject::set_y_pos(int y){
  obj_rect.y = y;  //sets y position of the object
}

int GameObject::get_x_vel(){
  return x_vel; //returns x position of the object
}

int GameObject::get_y_vel(){
  return y_vel; //returns the y velocity of the object
}

void GameObject::set_x_pos(int x){
  obj_rect.x = x;
}
void GameObject::set_x_vel(int vel){
  x_vel = vel;                            //sets the x velocity of the Object
  if(x_vel >= MAX_VEL) x_vel = MAX_VEL;
}

void GameObject::set_y_vel(int vel){
  y_vel = vel;                          //sets the y velocity of the object
  if(y_vel >= MAX_VEL) y_vel = MAX_VEL;
}

int GameObject::get_height(){
  return obj_rect.h; //returns the height of the object
}

int GameObject::get_width(){
  return obj_rect.w;  //returns the width of the object
}

SDL_Rect GameObject::get_rect(){
  return obj_rect;
}

void GameObject::set_height(int h){
  obj_rect.h = h;
}

void GameObject::set_width(int w){
  obj_rect.w = w;
}


