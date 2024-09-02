#include "Shape.hpp"
#include <SDL2/SDL.h>
#include <Node.hpp>
#include <vector>
#pragma once
namespace mt_cad{
	class Circle: public Shape{
		public:
			Circle(std::vector<mt_cad::Node> nodes);
			void draw(SDL_Renderer * ctx) ;
            bool hover(int x , int y) ;
            std::vector<mt_cad::Node> get_points() ;
            void set_points(std::vector<mt_cad::Node> nodes) ;
	};
}

