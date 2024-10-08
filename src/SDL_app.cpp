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

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL_app.hpp>
#include <cstdlib>
#include <iostream>
App::SDL_app::SDL_app(){
    if(SDL_Init(SDL_INIT_EVERYTHING)<0){
        //info when SDL fails
        std::cout << SDL_GetError() << std::endl;
        //exit program
        exit(-1);    
    }
    this->window = SDL_CreateWindow("curbas", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 720, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
    this->ctx = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    this->frames = 60;
    this->framerateTiming = 1000/this->frames;
}
int App::SDL_app::get_maxFrames(){return this->frames;}
void App::SDL_app::set_maxFrames(int frames){
    if (frames > 0){
        this->frames = frames;
        this->framerateTiming = 1000/this->frames;
    }else{
        std::cout << "No framerate chaged! Maybe negative frames?" << std::endl;
    }
 
}
void App::SDL_app::get_windowSize(int &w , int &h){
    int * _w;
    int * _h;
    SDL_GetWindowSize(this->window, _w, _h);
    w = *(_w);
    h = *(_h);
}
App::SDL_app::~SDL_app(){
    SDL_DestroyRenderer(this->ctx);
    SDL_DestroyWindow(this->window);
}