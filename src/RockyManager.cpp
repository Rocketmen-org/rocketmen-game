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
  remaining_movement = 0;
}

void RockyManager::update(){
  turn_over = true;

  if(attack){
    for(int i = 0; i < NUM_ROCKYS; i++){
      if(!rockys[i]->isDone()){
	turn_over = false; //runs if a single rocky isn't done
        if(rockys[i]->move(dest[i])){ //if finished moving
	  if (paths[i].size() > 0 && remaining_movement > 0){
            dest[i] = paths[i].back();
	    paths[i].pop_back();
	    remaining_movement--;
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
  remaining_movement = MOVEMENT;
  for(int i = 0; i < NUM_ROCKYS; i++){
    rockys[i]->setDone(false);
    dest[i].first = x;
    dest[i].second = y;

    coordinate_t cur_pos = make_pair(rockys[i]->get_rect().x/TILE_W, rockys[i]->get_rect().y/TILE_H);
    coordinate_t temp_dest = make_pair(dest[i].first/TILE_W, dest[i].second/TILE_H);

    //determine which adjacent side to target
    
    //upward
    coordinate_t dest_upward = make_pair(temp_dest.first, temp_dest.second - 1);
    int upward = abs(cur_pos.first - dest_upward.first) + abs(cur_pos.second - dest_upward.second);

    //downward
    coordinate_t dest_downward = make_pair(temp_dest.first, temp_dest.second + 1);
    int downward = abs(cur_pos.first - dest_downward.first) + abs(cur_pos.second - dest_downward.second);

    //rightward
    coordinate_t dest_rightward = make_pair(temp_dest.first + 1, temp_dest.second);
    int rightward = abs(cur_pos.first - dest_rightward.first) + abs(cur_pos.second - dest_rightward.second);

    //leftward
    coordinate_t dest_leftward = make_pair(temp_dest.first - 1, temp_dest.second);
    int leftward = abs(cur_pos.first - dest_leftward.first) + abs(cur_pos.second - dest_leftward.second);

    int min = upward;
    if (downward < min)
      min = downward;
    if (rightward < min)
      min = rightward;
    if (leftward < min)
      min = leftward;

    if (min == upward)
      temp_dest = dest_upward;
    if (min == downward)
      temp_dest = dest_downward;
    if (min == rightward)
      temp_dest = dest_rightward;
    if (min == leftward)
      temp_dest = dest_leftward;

    printf("finding path from %d, %d to %d, %d\n", cur_pos.first, cur_pos.second, temp_dest.first, temp_dest.second);
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

void RockyManager::reset(){
  alive = true;
  for(int i = 0; i < NUM_ROCKYS; i++){
    rockys[i]->set_x_pos(ROCKY_START_X);
    rockys[i]->set_y_pos(ROCKY_START_Y);
  }
}

bool RockyManager::adjacent(int x, int y){
  x /= TILE_W;
  y /= TILE_H;
  for(int i = 0; i < NUM_ROCKYS; i++){
    int rx = rockys[i]->get_x_pos() / TILE_W;
    int ry = rockys[i]->get_y_pos() / TILE_H;

    if (x >= rx - 1 && x <= rx + 1)
      return true;
     if (y >= ry - 1 && y <= ry + 1)
      return true;
  }
}
