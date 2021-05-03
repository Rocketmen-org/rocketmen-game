#include "textObject.h"

TextObject::TextObject(SDL_Renderer* ren) : GameObject(ren)
{
  obj_renderer = ren;
}

void TextObject::obj_update( const char* A )
{
  SDL_Surface *text_surface;

  if(!(text_surface=TTF_RenderText_Solid(obj_font, A, obj_color)))
  {
    std::cout << "error font: " << TTF_GetError() << std::endl;
  }
  else
  {
    // font loaded successfully

    obj_texture = SDL_CreateTextureFromSurface(obj_renderer,text_surface);
    SDL_FreeSurface(text_surface);

    int w,h;
    SDL_QueryTexture(obj_texture, NULL, NULL, &w, &h);

    obj_rect.w = w;
    obj_rect.h = h;

  }

}

void TextObject::text_color( SDL_Color newcolor )
{
   obj_color = newcolor;
}

void TextObject::obj_render()
{
  SDL_RenderCopy(obj_renderer, obj_texture, NULL, &obj_rect);
}
