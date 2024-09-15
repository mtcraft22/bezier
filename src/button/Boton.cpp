#include <button/Boton.hpp>
#include <SDL2/SDL_events.h>
#include <chrono>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>
#include <thread>
#define default(x) this->x = x;
Boton::Boton(int x,int y,int gapX,int gapY, SDL_Color color, SDL_Color colortext,std::string text,SDL_Event* e)
{
	this->text = text;
    this->el.e = *(e);
	this->x = x;
	this->y = y;
	this->w = 0;
	this->h = 0;
	this->color = color;
	this->colortext = colortext;
	this->gapX = gapX;
	this->gapY = gapY;
    this->stop = false;
	SDL_Rect col = { x,y,10,10 };
	this->box = &col;
    this->hilo = std::thread(&Boton::check_status,this);
}
    bool Boton::Is_hover(){
        return this->hover;
    }
    bool Boton::Is_clicked(){
        return this->pressed;
    }
    void Boton::set_evento(SDL_Event *e){
        this->el.e = *(e);
    }
    void Boton::check_status(){
     
        while (!this->stop) {
            el.lock();
            bool prev = this->hover;
            this->hover = false;
            this->pressed = false;
            this->hover = (this->el.e.motion.x > this->x && x < this->x + (this->w + (this->gapX*2))) && (this->el.e.motion.y > this->y && this->el.e.motion.y < this->y + (this->h + (this->gapY*2)));
         
            
            if (this->el.e.type == SDL_MOUSEBUTTONDOWN){
                    this->pressed = this->hover && this->el.e.button.button == SDL_BUTTON_LEFT ;
            }
            if (prev && !hover){
                if(this->on_hover_release){
                    std::cout << "hover_release" << std::endl;
                    this->on_hover_release();
                }
            }else{
                if(this->hover && !this->pressed){
                    if (this->on_hover){
                        std::cout << "hover" << std::endl;
                        this->on_hover();
                    }
                }
            }
            
            if(this->pressed){
                if (this->on_click){
                    this->on_click();
                }
            }
            el.unlock();
            std::chrono::milliseconds dura( 50 );
            std::this_thread::sleep_for( dura );
        }     
       
    }
    void Boton::getGap(int* gapX, int* gapY)
    {
        *(gapX) = this->gapX;
        *(gapY) = this->gapY;
    }

    void Boton::setGap(int gapX, int gapY)
    {
        this->gapX=gapX;
        this->gapY=gapY;
    }

    void Boton::getPos(int* x, int* y)
    {
        *(x) = this->x;
        *(y) = this->y;
    }

    void Boton::setPos(int x, int y)
    {
        this->x=x;
        this->y=y;
        this->box->x = x;
        this->box->y = y;
    }

    void Boton::getColor(SDL_Color* color, SDL_Color* colortext)
    {
        *(color) = this->color;
        *(colortext) = this->colortext;
    }

    void Boton::setColor(SDL_Color color, SDL_Color colortext)
    {
        this->color =color;
        this->colortext = colortext;
    }

   

    void Boton::render(SDL_Renderer* ctx, TTF_Font* font,SDL_Color * srccolor)
    {
        
        SDL_Color bg ={this->color.r,this->color.g,this->color.b,1};
        SDL_Color fg = {this->colortext.r,this->colortext.g,this->colortext.b,this->colortext.a};
        SDL_Surface* txt = TTF_RenderText_Shaded(font, this->text.c_str(), fg, bg);
        SDL_Texture* txt_text = SDL_CreateTextureFromSurface(ctx, txt);
        int w, h;
        SDL_QueryTexture(txt_text, NULL, NULL, &w, &h);
        this->w = w;
        this->h = h;
        SDL_Rect aux = { this->x ,this->y,w + (this->gapX * 2),h + (this->gapY*2) };

        SDL_SetRenderDrawColor(ctx, this->color.r, this->color.g, this->color.b, this->color.a);
        SDL_RenderFillRect(ctx, &aux);
        SDL_SetRenderDrawColor(ctx, srccolor->r, srccolor->g, srccolor->b, srccolor->a);

        SDL_Rect destTxt = { this->x + (this->gapX / 2),this->y + (this->gapY / 2),w + this->gapX,h + this->gapY };
        SDL_RenderCopy(ctx, txt_text, NULL, &destTxt);
        SDL_FreeSurface(txt);
        SDL_DestroyTexture(txt_text);
    }
    Boton::~Boton(){
        this->stop = true;
        this->hilo.join();
    }
