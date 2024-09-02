#include <Rectangle.hpp>
#include <Node.hpp>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
mt_cad::Node::Node(int x, int y,Restictions canmove) {
	this->x = x;
	this->y = y;
	this->canmove = canmove;
}
void mt_cad::Node::get_coords(int &x, int &y) {
	x = this->x;
	y = this->y;
}
Restictions mt_cad::Node::get_canmove(){return this->canmove;}
void mt_cad::Node::set_canmove(Restictions canmove){this->canmove = canmove;};
void mt_cad::Node::set_coords(int x, int y){
	switch (this->canmove) {
		case X:
			this->x = x;
			break;
		case Y:
			this->y = y;
			break;
		case XY:
			this->x = x;
			this->y = y;
			break;
	}


}
void mt_cad::Node::draw(SDL_Renderer *ctx) {
	SDL_Rect rect = {this->x-5, this->y-5,10,10};
	SDL_RenderDrawPoint(ctx, this->x, this->y);
	SDL_RenderDrawRect(ctx, &rect);
}
bool mt_cad::Node::hover(int mouse_x , int mouse_y){
	return (mouse_x > this->x-10 && mouse_x < this->x +5) && (mouse_y > this->y-5 && mouse_y < this->y +5);
}