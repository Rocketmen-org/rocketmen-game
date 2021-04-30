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

  
  rocky = new RockyManager(game_renderer); //create rocky
  rocky->init("./images/rocky_sprites.png");

  Red_Attack_Rect = new GameObject(game_renderer);
  Red_Attack_Rect->Obj_Init("./images/Red_Rect.xcf", 1, 60, PLAYER_START_X, PLAYER_START_Y, 3000, 3000, TILE_WIDTH, TILE_HEIGHT, 100);
  
  player->set_state("IDLE");

  Title_Screen = new GameObject(game_renderer); // creating title screen image
  Title_Screen->Obj_Init("./images/screen_title.png", 1, 1, 0, 0, 1920, 1800, SCREEN_WIDTH, SCREEN_HEIGHT, 255);
  Pause_Screen = new GameObject(game_renderer); //creating pause screen image
  Pause_Screen->Obj_Init("./images/screen_paused.png", 1, 1, 0, 0, 1920, 1800, SCREEN_WIDTH, SCREEN_HEIGHT, 255);
  BG = new GameObject(game_renderer); //creating pause screen image
  BG->Obj_Init("./images/background.png", 1, 1, 0, 0, 5000, 5000, LEVEL_WIDTH, LEVEL_HEIGHT, 255);
  
  Rocket_Red = new Red_Rocket(game_renderer);
  Rocket_Red->Obj_Init("./images/rocket_red.png", 1, 1, player->get_x_pos(), player->get_y_pos(), 3000, 3000, TILE_WIDTH, TILE_HEIGHT, 255);

  PE = new Particle_Emitter();
  
  Turn = "Player";
  Attack = "None";
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
      //if(Turn == "Attack"){
      //qualifyer to determine if attack is over
      //Turn == "Move";
      //}
      if(Turn == "Attack"){
	if(!Rocket_Red->is_alive()){
	  Turn = "Player";
	  player->set_state("Idle");
	}
      }
      if(Turn == "Move"){
	if((player->get_x_pos() == Move_Rect->get_x_pos()) && (player->get_y_pos() == Move_Rect->get_y_pos()))
	  Turn = "Player";
      }
      if(input.type == SDL_KEYDOWN && (Attack == "Red")){
	std::cout << "enter" << std::endl;
	switch(input.key.keysym.sym){
	case SDLK_a : 
	  //set rocket to fire left
	  //set attack rectangle to left
	  Red_Attack_Rect->set_x_pos(camera.x);
	  Red_Attack_Rect->set_y_pos(player->get_y_pos());
	  Red_Attack_Rect->set_width(player->get_x_pos() - camera.x);
	  Red_Attack_Rect->set_height(TILE_HEIGHT);
	  Rocket_Red->set_direction("Left");
	  break;
	case SDLK_d : 
	  //set roocket to fire right
	  //set attack rectangle to right
	  Red_Attack_Rect->set_x_pos(player->get_x_pos() + TILE_WIDTH);
	  Red_Attack_Rect->set_y_pos(player->get_y_pos());
	  Red_Attack_Rect->set_width((camera.x + camera.w) - (player->get_x_pos() + TILE_WIDTH));
	  Red_Attack_Rect->set_height(TILE_HEIGHT);
	   Rocket_Red->set_direction("Right");
	  break;
	case SDLK_w : 
	  //set rocket to fire up
	  //set attack rectangle to up
	  Red_Attack_Rect->set_x_pos(player->get_x_pos());
	  Red_Attack_Rect->set_y_pos(camera.y);
	  Red_Attack_Rect->set_width(TILE_WIDTH);
	  Red_Attack_Rect->set_height(player->get_y_pos() - camera.y);
	   Rocket_Red->set_direction("Up");
	  break;
	case SDLK_s :  
	  //set rocket to fire down
	  //set attack rectangle to down
	  Red_Attack_Rect->set_x_pos(player->get_x_pos());
	  Red_Attack_Rect->set_y_pos(player->get_y_pos() + TILE_HEIGHT);
	  Red_Attack_Rect->set_width(TILE_WIDTH);
	  Red_Attack_Rect->set_height((camera.y + camera.h) - (player->get_y_pos() + TILE_HEIGHT));
	   Rocket_Red->set_direction("Down");
	  break;
	case SDLK_j :
	  Attack = "None";
	  //set rectangle to none setting
	  Red_Attack_Rect->set_x_pos(player->get_x_pos());
	  Red_Attack_Rect->set_y_pos(player->get_y_pos());
	  Red_Attack_Rect->set_width(TILE_WIDTH);
	  Red_Attack_Rect->set_height(TILE_HEIGHT);
	  Rocket_Red->set_alive(false);
	  break;
	case SDLK_SPACE :
	  Attack = "Locked";
	  Turn = "Attack"; 
	  AP -= 1;
	  player->set_sprite(Rocket_Red->get_direction());
	  break;
	}
      }
      else if(input.type == SDL_KEYDOWN && (Turn == "Player") && ((Attack == "None")||(Attack == "Locked"))){
	switch(input.key.keysym.sym){
	case SDLK_a :  //move left
	  //state_choice = "RUNLEFT";
	  std::cout << "left" << std::endl;
	  if((Move_Rect->get_x_pos() - TILE_WIDTH) >= camera.x && MP > 0){ 
	    Move_Rect->set_x_pos(Move_Rect->get_x_pos() - TILE_WIDTH);
	  }
	  //player->set_state(state_choice);
	  break;
	case SDLK_d :  //move right
	  //state_choice = "RUNRIGHT";
	  std::cout << "right" << std::endl;
	  if((Move_Rect->get_x_pos() + (TILE_WIDTH*2)) <= (camera.x + camera.w) && MP > 0){ 
	    Move_Rect->set_x_pos(Move_Rect->get_x_pos() + TILE_WIDTH);
	  }
	  //player->set_state(state_choice);
	  break;
	case SDLK_w :    //move up
	  //state_choice = "RUNUP";
	  std::cout << "up" << std::endl;
	  if((Move_Rect->get_y_pos() - TILE_HEIGHT) >= camera.y  && MP > 0){ 
	    Move_Rect->set_y_pos(Move_Rect->get_y_pos() - TILE_HEIGHT);
	  }
	  //player->set_state(state_choice);
	  break;
	case SDLK_s :   //move down
	  //state_choice = "RUNDOWN";
	  std::cout << "down" << std::endl;
	  if((Move_Rect->get_y_pos() + (TILE_HEIGHT*2)) <= (camera.y + camera.h) && MP > 0){ 
	    Move_Rect->set_y_pos(Move_Rect->get_y_pos() + TILE_HEIGHT);
	  }
	  //player->set_state(state_choice);
	  break;
	case SDLK_j :
	  std::cout << "attack red" << std::endl;
	  //reset attack rect
	  Red_Attack_Rect->set_x_pos(player->get_x_pos());
	  Red_Attack_Rect->set_y_pos(player->get_y_pos());
	  Red_Attack_Rect->set_width(TILE_WIDTH);
	  Red_Attack_Rect->set_height(TILE_HEIGHT);
	  //reset move rect
	  Move_Rect->set_x_pos(player->get_x_pos());
	  Move_Rect->set_y_pos(player->get_y_pos());
	  Move_Rect->set_width(TILE_WIDTH);
	  Move_Rect->set_height(TILE_HEIGHT);
	  if(AP != 0){
	    Attack = "Red";
	    Rocket_Red->set_alive(true);
	    Rocket_Red->set_x_pos(player->get_x_pos());
	    Rocket_Red->set_y_pos(player->get_y_pos());
	  }
	  break;
	case SDLK_k :
	  //Attack = "Blue";
	  break;
	case SDLK_SPACE :
	  std::cout << "turn over" << std::endl;
	  //will later call Turn == "Attack";
	  Turn = "Move";
	  MP -= 1;
	  break;
	case SDLK_RETURN :
	  Turn = "Enemy";
	  break;

	} 
      }
      if(input.type == SDL_KEYDOWN){
	switch(input.key.keysym.sym){
	case SDLK_ESCAPE :
	  game_paused = true;
	  break;
	}
      }
    }
}

void GameEngine::UpdateMechanics(){

  // Check if the game is paused or in the title screen before doing anything
  if( game_titlescreen == false && game_paused == false ){
      //Move_Rect->Obj_Update();
      if(Turn == "Enemy"){
	std::cout << "enemy turn" << std::endl;
	if (rocky->defend()){
	  rocky->setAttack((rand() % 4 + 4) * 64, (rand() % 4 + 4) * 64); //start enemy attack
	}
	if(rocky->turnOver()){
	  rocky->setDefend(); //start enemy defense
	  Turn = "Player";
	  Attack = "None";
	  MP = 1;
	  AP = 1;
	}
      }
      else if(Turn == "Attack"){
	//some sort of rocket->Update();
	Rocket_Red->Obj_Update(camera);
	if(Rocket_Red->Collison(//rect of rocky)){
	  Rocket_Red->set_alive(false);
	  //kill rocky
	  PE->PE_Init("./images/FireWork_Pix.png", game_renderer, //position rocky is, ///rocky y, 7, 7, FIREWORK)  
	}
	player->Obj_Update(player->get_x_pos(), player->get_y_pos());
      }
      else if(Turn == "Move"){
	std::cout << "Move turn" << std::endl;
	//then once the attack phase i
	player->Obj_Update(Move_Rect->get_x_pos(), Move_Rect->get_y_pos()); //call update on object
	//set camera
	SetCamera();
      }
      else{
	player->Obj_Update(player->get_x_pos(), player->get_y_pos());
      }
      rocky->update(); //update enemy
      PE->Update();
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

void GameEngine::Collision_Res(

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
      BG->Obj_Render(camera.x, camera.y); //render background
      for(int i = 0; i < TOTAL_TILES; i++){ //render tiles
	Tiles[i]->Obj_Render(camera);
      }
      PE->draw(game_renderer); //render the particles
      player->Obj_Render(camera.x, camera.y); //render player
      rocky->render(camera.x, camera.y); //render enemy
      if((player->get_x_pos() != Move_Rect->get_x_pos()) || (player->get_y_pos() != Move_Rect->get_y_pos())){
	Move_Rect->Obj_Render(camera.x, camera.y); //render move selection
      }
      if(((player->get_x_pos() != Red_Attack_Rect->get_x_pos()) || (player->get_y_pos() != Red_Attack_Rect->get_y_pos())) && ((Attack == "Red")||(Attack == "Blue"))){
	Red_Attack_Rect->Obj_Render(camera.x, camera.y);
      }
      if(Rocket_Red->is_alive() && ((Rocket_Red->get_x_pos() != player->get_x_pos()) || (Rocket_Red->get_y_pos() != player->get_y_pos()))){
	Rocket_Red->Obj_Render(camera.x, camera.y);
      }
      // If game is paused, render the pause screen over gameplay.
      if( game_paused == true)
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
