#ifndef GameEngine_h
#define GameEngine_h

#include "game.h"
#include "player.h"
#include "Tiles.h"
#include "Background.h"
#include "Particle_Emitter.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int LEVEL_WIDTH = 1920;
const int LEVEL_HEIGHT = 704;
const int PLAYER_START_X = 64;
const int PLAYER_START_Y = 128;

const int Background_Size = 2;


const int TILE_WIDTH = 64;
const int TILE_HEIGHT = 64;
const int TOTAL_TILES = (LEVEL_WIDTH*LEVEL_HEIGHT)/(TILE_WIDTH * TILE_HEIGHT);
const int TOTAL_TILES_SPRITES = 6;

const int TILE_GROUNDLEFT = 00;
const int TILE_GROUNDCENTER = 01;
const int TILE_GROUNDRIGHT = 02;
const int TILE_ROCK_LEFT = 03;
const int TILE_ROCK_RIGHT = 04;
const int TILE_GROUND_PLANE = 05;

const int FIREWORK = 1;
const int MAX_PARTS_FIRE = 100;

class GameEngine{
public:
  void Init();

  bool Game_Is_Running();

  void HandleEvents();
  void UpdateMechanics();

  void SetCamera();
  void SetTiles();

  bool Collision_Det(SDL_Rect a, SDL_Rect b);
  void Collision_Res(Player* a, GameObject* b);

  void Render();

  void Quit();


protected:
  Player* player;

  //Blue_Rocket* rocket_blue
  //Red_Rocket* rocket_red

  GameObject* Move_Rect;

  GameObject* Red_Attack_Rect;
  GameObject* Title_Screen;
  GameObject* Pause_Screen;

  Particle_Emitter* PE;

  Background* BG[Background_Size];

  Tile* Tiles[TOTAL_TILES];


  SDL_Window* game_window = NULL;
  SDL_Renderer* game_renderer = NULL;
  SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

  bool game_titlescreen = true;
  bool game_paused = false;
  bool is_running = true;
  string Turn;
  string Attack;
  int AP = 1;
  int MP = 1;
};

#endif

