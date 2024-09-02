#pragma once
#include <Shape.hpp>
#include <vector>
namespace mt_cad {
    class Node;
    class Rectangle: public Shape{
        public:
            Rectangle(std::vector<mt_cad::Node> nodes);
            void draw(SDL_Renderer * ctx) ;
            bool hover(int x , int y) ;
            std::vector<mt_cad::Node> get_points() ;
            void set_points(std::vector<mt_cad::Node> nodes) ;
    };
}