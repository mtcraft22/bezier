#include <GUI/ImageButton.hpp>
#include <SDL2/SDL.h>

void GUI::ImageButton::render(SDL_Renderer * ctx){
    int w,h;
    SDL_QueryTexture(this->img,NULL, NULL, &w, &h);
    SDL_Rect dest = {this->x,this->y,w,h};
    SDL_RenderCopy(ctx, this->img,NULL, &dest);
}