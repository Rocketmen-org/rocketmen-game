#include "GameEngine.h"
#include "game.h"


int main(){
  int start_time;
  int duration;
  int FPS = 1000 / 60;
  
  GameEngine* GE = new GameEngine;
  TTF_Init();
  GE->Init();

  while(GE->Game_Is_Running()){
    start_time = SDL_GetTicks();

    GE->HandleEvents();
    GE->UpdateMechanics();
    GE->Render();

    duration = SDL_GetTicks() - start_time;
    if(duration < FPS){
      SDL_Delay(FPS - duration);
    }
  }

  GE->Quit();

  return 0;
}
