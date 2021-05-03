#include "game.h"
#include "GameObject.h"

class TextObject : public GameObject
{
public:
  TextObject(SDL_Renderer* ren);
  ~TextObject();

  // Have to implement this in here for LITERALLY No reason
  void obj_init( const char* ttf_file, int start_x, int start_y, SDL_Color start_color, int size)
  {
    obj_font = TTF_OpenFont(ttf_file,size);

    if(!obj_font){
      std::cout << "Font did not load" << std::endl;
    }

    obj_rect.x = start_x;
    obj_rect.y = start_y;

    obj_color = start_color;
  }

  void obj_update( const char* A );
  void text_color( SDL_Color );
  void obj_render();

private:

  SDL_Color obj_color;
  TTF_Font* obj_font;

};
