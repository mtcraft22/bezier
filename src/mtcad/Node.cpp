/*
    Copyright (C) 2024 mtcraft22(Marc Tort Pascual) 
    This file is part of Bezier.

    Bezier is free software: 
    you can redistribute it and/or modify it under the terms 
    of the GNU General Public License as published by the Free Software Foundation, 
    either version 3 of the License, or (at your option) any later version.
    Bezier is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
    without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
    See the GNU General Public License for more details.
    You should have received a copy of the GNU General Public License along with Bezier. If not, see <https://www.gnu.org/licenses/>. 
*/
#include <mtcad/Rectangle.hpp>
#include <mtcad/Node.hpp>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
mt_cad::Node::Node(float x, float y,Restictions canmove) {
	this->x = x;
	this->y = y;
	this->canmove = canmove;
}
void mt_cad::Node::get_coords(float &x, float &y) {
	x = this->x;
	y = this->y;
}
Restictions mt_cad::Node::get_canmove(){return this->canmove;}
void mt_cad::Node::set_canmove(Restictions canmove){this->canmove = canmove;};
void mt_cad::Node::set_coords(float x, float y){
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
	SDL_FRect rect = {this->x-10, this->y-10,20,20};
	SDL_RenderDrawPointF(ctx, this->x, this->y);
	SDL_RenderDrawRectF(ctx, &rect);
}
bool mt_cad::Node::hover(float mouse_x , float mouse_y){
	return (mouse_x > this->x-10 && mouse_x < this->x +10) && (mouse_y > this->y-10 && mouse_y < this->y +10);
}
float mt_cad::Node::get_angle(){
    return this->angle;
}
void mt_cad::Node::set_angle(float angle){
    
    this->angle = angle;
}