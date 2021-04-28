#include "Particle.h"

Particle::Particle(){}


void Particle::obj_init(const char* graphic, SDL_Renderer* ren, int X, int Y, int W,int H){
  //initalize the object texture
  obj_renderer = ren;
  SDL_Surface* hold = IMG_Load(graphic);
  obj_graphic = SDL_CreateTextureFromSurface(obj_renderer, hold);

  SDL_FreeSurface(hold);

  //initalize the location and size of the particle
  obj_rect.x = X;
  obj_rect.y = Y;
  obj_rect.w = W;
  obj_rect.h = H;

  //set up base values for velocity
  x_vel = 0;
  y_vel = 0;
}

void Particle::Draw_FireWork(SDL_Renderer* ren){
  //draw particle with fading atribute
  if(lifetime > 0){ //only render if the particle is alive
    SDL_SetTextureAlphaMod(obj_graphic, (255 * lifetime)/10);
    SDL_RenderCopy(ren, obj_graphic, NULL, &obj_rect);
  }
  else{
    SDL_SetTextureAlphaMod(obj_graphic, 255); 
  }
}
 
void Particle::Update_FireWork(){
  if(lifetime > 0){ //only update if the particle is alive
    obj_rect.x += x_vel; //update the x position of the particle
    static int counter = 0;
    if(counter == 10){ //apply gravity to the particle every 10 frames
      y_vel += 1; //gravity
      counter = 0;
    }
    else{
      counter++;
    }
    obj_rect.y += y_vel; //set the y position of the particle
    lifetime--; //decriment the life time of the particle
  }
}


void Particle::set_x_vel(int vel){
  x_vel = vel; //set the x velocity of the particle
}

void Particle::set_y_vel(int vel){
  y_vel = vel; //set the y velocity of the particle
}

void Particle::set_lifetime(int life){
  lifetime = life; //set the lifetime of the particle
}

void Particle::destroy(){
}
