#pragma once

#include "Shape.hpp"
#include <SDL2/SDL_render.h>
class Line : public mt_cad::Shape{
    public:
        void draw(SDL_Texture * txt) ;
        bool hover(int x , int y) ;
        std::vector<mt_cad::Node> get_points() ;
        void set_points(std::vector<mt_cad::Node> nodes) ;
};