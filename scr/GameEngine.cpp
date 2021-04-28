#include "GameEngine.h"
#include "player.h"
#include "Tiles.h"
#include "Particle_Emitter.h"


void GameEngine::Init(){
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
  }
  //Enable gpu_enhanced textures
  IMG_Init(IMG_INIT_PNG);

  game_window = SDL_CreateWindow("my_game",
			       SDL_WINDOWPOS_CENTERED,
			       SDL_WINDOWPOS_CENTERED,
			       SCREEN_WIDTH,
			       SCREEN_HEIGHT, 0);
  game_renderer = SDL_CreateRenderer(game_window,-1,0);
  player = new Player(game_renderer); //create the player
  player->Obj_Init("./images/char1.png", 1, 60, 50, (SCREEN_HEIGHT - 300), 3000, 3000, 100, 100);
  player->set_state("IDLE");

  Pause_Screen = new GameObject(game_renderer); //creating pause screen image
  Pause_Screen->Obj_Init("./images/paused.png", 1, 1, 0, 0, 1920, 1800, SCREEN_WIDTH, SCREEN_HEIGHT);

  PE = new Particle_Emitter();
  SetTiles();

}

bool GameEngine::Game_Is_Running(){
  return is_running; //for checking if game is running
}

void GameEngine::HandleEvents(){
  SDL_Event input;
  string state_choice;
  SDL_PollEvent(&input);
  if(input.type == SDL_QUIT) is_running = false;

  if( game_paused == true )
  {
    if(input.type == SDL_KEYDOWN) // need this because otherwise game always takes two inputs ._.
    {
      switch(input.key.keysym.sym)
      {
        case SDLK_ESCAPE :
          is_running = false;
          break;
        case SDLK_RETURN :
          game_paused = false;
          break;
        case SDLK_i :

      }
    }
  }
  else
  {
    if(input.type == SDL_KEYDOWN){
      switch(input.key.keysym.sym){
      case SDLK_LEFT :  //move left
        state_choice = "RUNLEFT";
        std::cout << "left" << std::endl;
        player->set_state(state_choice);
        break;
      case SDLK_RIGHT :  //move right
        state_choice = "RUNRIGHT";
        std::cout << "right" << std::endl;
        player->set_state(state_choice);
        break;
      case SDLK_UP :    //move up
        state_choice = "RUNUP";
        std::cout << "up" << std::endl;
        player->set_state(state_choice);
        break;
      case SDLK_DOWN :   //move down
        state_choice = "RUNDOWN";
        std::cout << "down" << std::endl;
        player->set_state(state_choice);
        break;
      case SDLK_ESCAPE :
        game_paused = true;
        break;
      }
    }
    else if(input.type == SDL_KEYUP){ //if a key is lifted then switch to idle from that key
      std::cout << "keyup" << std::endl;

      switch(input.key.keysym.sym){
      case SDLK_LEFT :  //move left
      	if(player->get_state() == "RUNLEFT"){
      	  state_choice = "IDLE";
      	  std::cout << "idle from left up" << std::endl;
      	  player->set_state(state_choice);
        }
        break;
      case SDLK_RIGHT :  //move right
      	if(player->get_state() == "RUNRIGHT"){
      	  state_choice = "IDLE";
      	  std::cout << "idle from right up" << std::endl;
      	  player->set_state(state_choice);
        }
        break;
      case SDLK_UP :
      	if(player->get_state() == "RUNUP"){
      	  state_choice = "IDLE";
      	  std::cout << "idle from up up" << std::endl;
      	  player->set_state(state_choice);
        }
        break;
      case SDLK_DOWN:
        if(player->get_state() == "RUNDOWN"){
    	    state_choice = "IDLE";
  	      std::cout << "idle from down up" << std::endl;
  	      player->set_state(state_choice);
        }
        break;
      }
    }
  }
}

void GameEngine::UpdateMechanics(){

  if( game_paused == false )
  {
    player->Obj_Update(); //call update on object
    /*for(int i = Background_Size - 1; i >= 0; i--){ //update the background elements
      BG[i]->BG_Update(player->get_state(), player->get_x_pos());
      }*/
    //set camera
    SetCamera();

    PE->Update(); //call update on particle emitter
  }

}


void GameEngine::SetCamera(){
  //set the camera to follow the player and be centered on the middle of the screen
  camera.x = (player->get_x_pos() + player->get_width()/2) - SCREEN_WIDTH/2;
  camera.y = (player->get_y_pos() + player->get_height()/2) - SCREEN_HEIGHT/2;
  //make sure camera doesn't go out of bounds of the level
  if(camera.x < 0){
    camera.x = 0;
  }
  if(camera.y < 0){
    camera.y = 0;
  }
  if(camera.x  > LEVEL_WIDTH - camera.w){
    camera.x = LEVEL_WIDTH - camera.w;  }
  if(camera.y > LEVEL_HEIGHT - camera.h){
    camera.y = LEVEL_HEIGHT - camera.h;
  }
}

void GameEngine::SetTiles(){
  //set up tiles locations by reading in map and making the tile objects
  int x = 0, y = 0;
  std::ifstream map("./world/tiles.map");
  if(map.fail()){
    std::cout << "Unable to load map file" << std::endl;
    return;
  }
  else{
    for(int i = 0; i < TOTAL_TILES; i++){
      int tile_type_temp = -1;
      map >> tile_type_temp;

      if((tile_type_temp >= 0) && (tile_type_temp < TOTAL_TILES_SPRITES)){
	Tiles[i] = new Tile(game_renderer);
	Tiles[i]->Obj_Init( x, y, tile_type_temp);
	x += TILE_WIDTH;
	if(x == LEVEL_WIDTH){
	  x = 0;
	  y += TILE_HEIGHT;
	}
      }
    }
  }
}


bool GameEngine::Collision_Det(SDL_Rect a, SDL_Rect b){
  //create one box
  int Left_A = a.x + 40;
  int Right_A = Left_A + a.w - 40;
  int Top_A = a.y;
  int Bottom_A = Top_A + a.h;
  //create another box
  int Left_B = b.x;
  int Right_B = Left_B + b.w;
  int Top_B = b.y;
  int Bottom_B = Top_B + b.h;

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

void GameEngine::Collision_Res(Player* a, GameObject* b){
  //handles player reaching finishing flag
  if(b == Finish_Flag){
    a->set_x_pos(Start_Flag->get_x_pos()); //set player back to the start

    PE->PE_Init("../Assignment_4/Images/FireWork_Pix.png", game_renderer, (a->get_x_pos() + 20), 180, 7, 7, FIREWORK); //play a firework particle animation for the player

  }
}

void GameEngine::Render(){
  //set background color
  SDL_SetRenderDrawColor(game_renderer, 135, 206, 235, 255);
  //clear screen
  SDL_RenderClear(game_renderer);

  /*for(int i = Background_Size - 1; i >= 0; i--){ //render background
  BG[i]->BG_Render();
  }*/

  for(int i = 0; i < TOTAL_TILES; i++){ //render tiles
    Tiles[i]->Obj_Render(camera);
  }


  PE->draw(game_renderer); //render the particles

  player->Obj_Render(camera.x, camera.y); //render player

  if( game_paused == true )
  {
    Pause_Screen->Obj_Render(0,0);
  }

  SDL_RenderPresent(game_renderer); //present game
}

void GameEngine::Quit(){
  SDL_DestroyRenderer(game_renderer);
  SDL_DestroyWindow(game_window);

  IMG_Quit();
  SDL_Quit();
}
