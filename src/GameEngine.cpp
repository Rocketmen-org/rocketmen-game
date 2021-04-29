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
  player->Obj_Init("./images/char1_sprites.png", 1, 60, PLAYER_START_X, PLAYER_START_Y, 500, 500, TILE_WIDTH, TILE_HEIGHT, 255);
  Move_Rect = new GameObject(game_renderer);
  Move_Rect->Obj_Init("./images/Move_Img.xcf", 1, 60, PLAYER_START_X, PLAYER_START_Y, 3000, 3000, TILE_WIDTH, TILE_HEIGHT, 100);
  player->set_state("IDLE");

  Title_Screen = new GameObject(game_renderer); // creating title screen image
  Title_Screen->Obj_Init("./images/titlescreen.png", 1, 1, 0, 0, 1920, 1800, SCREEN_WIDTH, SCREEN_HEIGHT, 255);
  Pause_Screen = new GameObject(game_renderer); //creating pause screen image
  Pause_Screen->Obj_Init("./images/paused.png", 1, 1, 0, 0, 1920, 1800, SCREEN_WIDTH, SCREEN_HEIGHT, 255);

  Turn = "Player";
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

  // If game is in the title screen, don't update other events!
  if( game_titlescreen == true )
  {
    if(input.type == SDL_KEYDOWN) // need this because otherwise game always takes two inputs ._.
    {
      switch(input.key.keysym.sym)
      {
        case SDLK_ESCAPE :
          is_running = false;
          break;
        case SDLK_RETURN :
          //start the game!
          game_titlescreen = false;
          break;

      }
    }
  }
  // If game is paused, don't update other events!
  else if( game_paused == true )
  {
    if(input.type == SDL_KEYDOWN) // need this because otherwise game always takes two inputs ._.
    {
      switch(input.key.keysym.sym)
      {
        case SDLK_ESCAPE :
          game_titlescreen = true;
          game_paused = false;
          break;
        case SDLK_RETURN :
          game_paused = false;
          break;

      }
    }
  }
  // Run events normally
  else
  {
    if(Turn == "Move"){
      if((player->get_x_pos() == Move_Rect->get_x_pos()) && (player->get_y_pos() == Move_Rect->get_y_pos()))
        Turn = "Player";
    }
    if(input.type == SDL_KEYDOWN && (Turn == "Player")){
      switch(input.key.keysym.sym){
        case SDLK_LEFT :  //move left
          std::cout << "left" << std::endl;
          if((Move_Rect->get_x_pos() - TILE_WIDTH) >= camera.x){
    	       Move_Rect->set_x_pos(Move_Rect->get_x_pos() - TILE_WIDTH);
          }
          break;
        case SDLK_RIGHT :  //move right
          std::cout << "right" << std::endl;
          if((Move_Rect->get_x_pos() + (TILE_WIDTH*2)) <= (camera.x + camera.w)){
    	       Move_Rect->set_x_pos(Move_Rect->get_x_pos() + TILE_WIDTH);
          }
          break;
        case SDLK_UP :    //move up
          std::cout << "up" << std::endl;
          if((Move_Rect->get_y_pos() - TILE_HEIGHT) >= camera.y){
    	       Move_Rect->set_y_pos(Move_Rect->get_y_pos() - TILE_HEIGHT);
          }
          break;
        case SDLK_DOWN:   //move down
          std::cout << "down" << std::endl;
          if((Move_Rect->get_y_pos() + (TILE_HEIGHT*2)) <= (camera.y + camera.h)){
      	      Move_Rect->set_y_pos(Move_Rect->get_y_pos() + TILE_HEIGHT);
          }
          break;
        case SDLK_SPACE:
          std::cout << "turn over" << std::endl;
          //will later call Turn == "Attack";
          Turn = "Move";
          break;
        case SDLK_ESCAPE :
          game_paused = true;
          break;
      }
    }

  }
}

void GameEngine::UpdateMechanics(){

  // Check if the game is paused or in the title screen before doing anything
  if( game_titlescreen == false && game_paused == false )
  {
    if(Turn == "Attack"){
      //some sort of rocket->Update();
    }
    if(Turn == "Move"){
      std::cout << "Move turn" << std::endl;
      //then once the attack phase i
      player->Obj_Update(Move_Rect->get_x_pos(), Move_Rect->get_y_pos()); //call update on object
      //set camera
      SetCamera();
    }
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
}

void GameEngine::Render(){
  //set background color
  SDL_SetRenderDrawColor(game_renderer, 135, 206, 235, 255);
  //clear screen
  SDL_RenderClear(game_renderer);

  // If in title screen, only render that.
  if( game_titlescreen == true )
  {
    Title_Screen->Obj_Render(0,0);
  }
  else
  {
    for(int i = 0; i < TOTAL_TILES; i++){ //render tiles
      Tiles[i]->Obj_Render(camera);
    }
    PE->draw(game_renderer); //render the particles
    player->Obj_Render(camera.x, camera.y); //render player
    if((player->get_x_pos() != Move_Rect->get_x_pos()) || (player->get_y_pos() != Move_Rect->get_y_pos())){
      Move_Rect->Obj_Render(camera.x, camera.y); //render move selection
    }

    // If game is paused, render the pause screen over gameplay.
    if( game_paused == true )
    {
      Pause_Screen->Obj_Render(0,0);
    }
  }

  SDL_RenderPresent(game_renderer); //present game
}

void GameEngine::Quit(){
  SDL_DestroyRenderer(game_renderer);
  SDL_DestroyWindow(game_window);

  IMG_Quit();
  SDL_Quit();
}
