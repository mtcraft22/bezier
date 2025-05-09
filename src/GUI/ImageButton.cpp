#include <GUI/ImageButton.hpp>
#include <SDL2/SDL.h>
#include <iostream>
#include <ostream>

GUI::ImageButton::ImageButton(
		SDL_Texture *img, 
		int x, int y, 
		SDL_Color bg, 
		SDL_Color fg, 
		std::string text,
		SDL_Event *e,
		int gapy , 
		int gapx 
	):GUI::Boton(x,y,gapx,gapy,bg,fg,"",e),img(img) 
	{
		SDL_QueryTexture(img,NULL,NULL,&this->w,&this->h);
		this->click = Callback<ImageButton, class T>();
		this->hover = Callback<ImageButton, class T>();
		this->hover_release = Callback<ImageButton, class T>();
	}

void GUI::ImageButton::render(SDL_Renderer * ctx){

	int w, h;
	SDL_QueryTexture(this->img, NULL, NULL, &w, &h);

	SDL_Rect aux = { this->x ,this->y,w + (this->gapX ),h + (this->gapY) };

	SDL_SetRenderDrawColor(ctx, this->bg.r, this->bg.g, this->bg.b, this->bg.a);
	SDL_RenderFillRect(ctx, &aux);

	//SDL_SetRenderDrawColor(ctx, this->fg.r, this->fg.g, this->fg.b, this->bg.a);

	SDL_Rect destTxt = { this->x + (this->gapX / 2),this->y + (this->gapY / 2),w ,h  };
	SDL_RenderCopy(ctx, this->img, NULL, &destTxt);
}
