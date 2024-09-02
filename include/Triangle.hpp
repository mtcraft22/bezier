#pragma once
#include <Node.hpp>
#include <Shape.hpp>
#include <vector>
namespace mt_cad {
    class Triangle: public Shape{
        public:
            Triangle (std::vector<mt_cad::Node> points );
            void draw(SDL_Renderer * ctx) ;
            bool hover(int x , int y) ;
            std::vector<mt_cad::Node> get_points() ;
            void set_points(std::vector<mt_cad::Node> nodes) ;
        private:
            bool triPoint(float x1, float y1, float x2, float y2, float x3, float y3,
            float px, float py);
    };
}