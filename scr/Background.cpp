#include "Background.h"
#include "GameEngine.h"

Background::Background(SDL_Renderer* ren){
  game_renderer = ren; 
}

Background::~Background(){}

void Background::BG_Init(const char* image, int width, int height, int y, int w, int h, int lay){
  SDL_Surface* hold = IMG_Load(image);
  BG_image = SDL_CreateTextureFromSurface(game_renderer, hold);
  SDL_FreeSurface(hold);

  image_width = width;
  image_height = height;
  layer = lay;
  Window.w = SCREEN_WIDTH;
  Window.h = SCREEN_HEIGHT;
  Window.x = 0;
  Window.y = y;

  BG_rect.x = 0;
  BG_rect.y = 0;
  BG_rect.w = w;
  BG_rect.h = h;
}

void Background::BG_Update(string state, int player_x_pos){
  if(player_x_pos + 40 <= LEVEL_WIDTH - SCREEN_WIDTH/2 && player_x_pos + 80 >= SCREEN_WIDTH/2){
    //if the player is in the middle of the screen the background moves
    //so once the player is at the ends of the levels it doesnt move
  /*if(state == "RUNLEFT"){
    if(BG_rect.x <= 0){
      Window.x += (int) (5 * 1/layer);
    }
    //std::cout << "background left" << std::endl;
    else BG_rect.x -= (int)(5 * 1/layer); // (int)(1/layer);
    if(Window.x >= SCREEN_WIDTH){
      BG_rect.x = image_width - BG_rect.w;
      Window.x = 0;
    }
  }
  else*/ if(state == "RUNRIGHT"){
      //std::cout << "background right" << std::endl;
      //* (int)(1/layer);
      //std::cout << "exit background update" << std::endl;
      if(BG_rect.x  + BG_rect.w >= image_width){
	Window.x -= (int) (5 * 1/layer);
      }
      else BG_rect.x += (int)(5 * 1/layer);
      if(Window.x <= -SCREEN_WIDTH){
	std::cout << "reset BG" << std::endl;
	BG_rect.x = 0;
	Window.x = 0;
      }
    }
  }
}

void Background::BG_Render(){
  if(BG_rect.x  + BG_rect.w >= image_width){ //create a second rectangle to simulate infinite loop
    SDL_Rect BG_rect2;
    SDL_Rect Window2;
    Window2.x = SCREEN_WIDTH + Window.x;
    Window2.y = 0;
    Window2.w = SCREEN_WIDTH;
    Window2.h = SCREEN_HEIGHT;
    BG_rect2.x = 0;
    BG_rect2.y = 0;
    BG_rect2.w = BG_rect.w;
    BG_rect2.h = BG_rect.h;
    SDL_RenderCopy(game_renderer, BG_image, &BG_rect, &Window); //render both rectangles
    SDL_RenderCopy(game_renderer, BG_image, &BG_rect2, &Window2);
  }
  /*if(BG_rect.x <= 0){
    SDL_Rect BG_rect2;
    SDL_Rect Window2;
    Window2.x = Window.x - SCREEN_WIDTH;
    Window2.y = 0;
    Window2.w = SCREEN_WIDTH;
    Window2.h = SCREEN_HEIGHT;
    BG_rect2.x = image_width - BG_rect.w;
    BG_rect2.y = 0;
    BG_rect2.w = BG_rect.w;
    BG_rect2.h = BG_rect.h;
     std::cout << "emake leftttt" << std::endl;
    std::cout << Window.x << std::endl;
    std::cout << Window2.x << std::endl;
    SDL_RenderCopy(game_renderer, BG_image, &BG_rect, &Window);
    SDL_RenderCopy(game_renderer, BG_image, &BG_rect2, &Window2); 
    }*/
  else{
    //only main rect is visable
    SDL_RenderCopy(game_renderer, BG_image, &BG_rect, &Window);
  }
}
