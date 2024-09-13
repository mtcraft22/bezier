#pragma once
#include <SDL2/SDL_render.h>
#include <vector>

namespace mt_cad {
    class Node;
    class Shape{
        public:
            virtual void draw(SDL_Renderer * ctx) = 0;
            virtual bool hover(int x , int y) = 0;
            virtual std::vector<mt_cad::Node> get_points() = 0;
            virtual void set_points(std::vector<mt_cad::Node> nodes) = 0;
        protected:
            int max_nodes;
            std::vector<mt_cad::Node> nodes;
    };
} 