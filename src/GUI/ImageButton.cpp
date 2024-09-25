#include <GUI/ImageButton.hpp>
#include <SDL2/SDL.h>
GUI::ImageButton::ImageButton(SDL_Texture *img, int x, int y, SDL_Color color, SDL_Color colortext, std::string text,
							  SDL_Event *e):GUI::Boton(x,y,0,0,color,colortext,"",e),img(img) {
                                this->hilo = std::thread(&GUI::ImageButton::check_status,this);
                              }
void GUI::ImageButton::render(SDL_Renderer * ctx){
    int w,h;
    SDL_QueryTexture(this->img,NULL, NULL, &w, &h);
    SDL_Rect dest = {this->x,this->y,w,h};
    SDL_RenderCopy(ctx, this->img,NULL, &dest);
}