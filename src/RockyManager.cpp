#include "RockyManager.h"

RockyManager::RockyManager(SDL_Renderer* ren){
  obj_renderer = ren;
}

RockyManager::~RockyManager(){}

void RockyManager::init(const char* image){
  //load image

  for(int i = 0; i < NUM_ROCKYS; i++){
    //create rockys
    Rocky* temp = new Rocky(obj_renderer);

    //init Rockys
    temp->Obj_Init(image, 1, 60, ROCKY_START_X, ROCKY_START_Y, 500, 500, 64, 64, 255);
    struct coordinate temp_dest; //starting coordinates
    temp_dest.x = ROCKY_START_X;
    temp_dest.y = ROCKY_START_Y;
    dest.push_back(temp_dest);
    rockys.push_back(temp);
  }

  attack = false;
  turn_over = false;
  alive = true;
}

void RockyManager::update(){
  turn_over = true;

  if(attack){
    for(int i = 0; i < NUM_ROCKYS; i++){
      if(!rockys[i]->isDone()){
	turn_over = false; //runs if a single rocky isn't done
        if(rockys[i]->move(dest[i])){ //if finished moving
          rockys[i]->attack(); //attack
          rockys[i]->setDone(true);
        }
      }
    }
  }
  else {
    for(int i = 0; i < NUM_ROCKYS; i++){
      rockys[i]->Obj_Update();
    }
  }
}

void RockyManager::render(int x, int y){
  if (alive){
    for(int i = 0; i < NUM_ROCKYS; i++){
      rockys[i]->Obj_Render(x, y);
    }
  }
}

void RockyManager::quit(){}

bool RockyManager::turnOver(){return turn_over;}

bool RockyManager::defend(){return !attack;}

void RockyManager::setAttack(int x, int y){
  attack = true;
  turn_over = false;
  for(int i = 0; i < NUM_ROCKYS; i++){
    rockys[i]->setDone(false);
    dest[i].x = x;
    dest[i].y = y;
  }
}

void RockyManager::setDefend(){attack = false;}

SDL_Rect RockyManager::getRect(){
  return rockys[0]->get_rect();
}

void RockyManager::kill(){
  alive = false;
}
