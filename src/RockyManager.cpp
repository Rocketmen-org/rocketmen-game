#include "RockyManager.h"

RockyManager::RockyManager(SDL_Renderer* ren) : paths(NUM_ROCKYS, vector<coordinate_t>{}){
  obj_renderer = ren;
  map = new Map(12, 12);
}

RockyManager::~RockyManager(){}

void RockyManager::init(const char* image){
  //load image

  for(int i = 0; i < NUM_ROCKYS; i++){
    //create rockys
    Rocky* temp = new Rocky(obj_renderer);

    //init Rockys
    temp->Obj_Init(image, 1, 60, ROCKY_START_X, ROCKY_START_Y, 500, 500, 64, 64, 255);
    coordinate_t temp_dest; //starting coordinates
    temp_dest.first = ROCKY_START_X;
    temp_dest.second = ROCKY_START_Y;
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
	  if (paths[i].size() > 0){
            dest[i] = paths[i].back();
	    paths[i].pop_back();
	  }
	  else{
            rockys[i]->attack(); //attack
            rockys[i]->setDone(true);
	  }
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
    dest[i].first = x;
    dest[i].second = y;

    coordinate_t cur_pos = make_pair(rockys[i]->get_rect().x/TILE_W, rockys[i]->get_rect().y/TILE_H);
    coordinate_t temp_dest = make_pair(dest[i].first/TILE_W, dest[i].second/TILE_H);
    printf("finding path from %d, %d to %d, %d\n", cur_pos.first, cur_pos.second, temp_dest.first, temp_dest.second);
    map->block(make_pair(4, 5), true);
    map->block(make_pair(5, 6), true);
    map->block(make_pair(6, 5), true);
    map->block(make_pair(7, 6), true);
    paths[i] = map->getPath(cur_pos, temp_dest);

    //paths[i] = map->getPath(make_pair(1,1), make_pair(10,1));
    printf("returned vector of size %lu\n", paths[i].size());
    for(auto path : paths[i]){
      printf("%d, %d\n", path.first, path.second);
    }

    dest[i] = paths[i].back();
    paths[i].pop_back();
  }
}

void RockyManager::setDefend(){attack = false;}

SDL_Rect RockyManager::getRect(){
  return rockys[0]->get_rect();
}

void RockyManager::kill(){
  alive = false;
}
