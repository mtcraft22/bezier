#include <Shape.hpp>
#include <SDL2/SDL.h>
#include <Node.hpp>
#include <vector>
#pragma once
namespace mt_cad {
    class Curve: public mt_cad::Shape {
        
        public:
            Curve (std::vector<mt_cad::Node> points );
            void draw(SDL_Renderer * ctx) ;
            bool hover(int x , int y) ;
            std::vector<mt_cad::Node> get_points() ;
            void set_points(std::vector<mt_cad::Node> nodes) ;
        private:
            bool triPoint(float x1, float y1, float x2, float y2, float x3, float y3,
            float px, float py);
      
          
    };
} ;
