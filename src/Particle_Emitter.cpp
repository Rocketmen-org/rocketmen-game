#include "Particle_Emitter.h"
#include "GameEngine.h"

Particle_Emitter::Particle_Emitter(){}

void Particle_Emitter::PE_Init(const char* graphic, SDL_Renderer* ren, int X, int Y, int W, int H, int type){
  srand(5); //set up seed for random number generator
  part_type = type; //assign the type of particle
  
  int max_parts = MAX_PARTS;
  if(part_type == FIREWORK){ 
    max_parts = MAX_PARTS_FIRE; //set amount of particles to the amount for the type
   
    for(int i = 0; i < max_parts; i++){ //loop through and create each particle
      particles[i] = new Particle();
     
      particles[i]->obj_init(graphic, ren, X, Y, W, H);
  
      particles[i]->set_x_vel(5 - (rand() % 100)/10); //randomly choose a x vel
      particles[i]->set_y_vel(5 - (rand() % 100)/10); //randomly choose a y vel
      particles[i]->set_lifetime(20 + (rand() % 100)); //randomly determine the lifetime
     
    }
  }
}

void Particle_Emitter::Update(){
  int max_parts = MAX_PARTS;
  
  if(part_type == FIREWORK){
    max_parts = MAX_PARTS_FIRE;
    for(int i = 0; i < max_parts; i++){
      particles[i]->Update_FireWork(); //call update on each particle
    }
  }
}

void Particle_Emitter::draw(SDL_Renderer* ren){
   int max_parts = MAX_PARTS;

  if(part_type == FIREWORK){
    max_parts = MAX_PARTS_FIRE;
    for(int i = 0; i < max_parts; i++){
      particles[i]->Draw_FireWork(ren); //call render on each particle
    }
  }
}
