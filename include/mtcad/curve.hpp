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
#include <mtcad/Shape.hpp>
#include <SDL2/SDL.h>
#include <mtcad/Node.hpp>
#include <string>
#include <vector>
#include <mtcad/materials.hpp>
#pragma once
namespace mt_cad {
    class Curve: public mt_cad::Shape {
        
        public:
            
            Curve (std::vector<mt_cad::Node> points );
            void draw(SDL_Renderer * ctx) ;
            bool hover(int x , int y) ;
            std::vector<mt_cad::Node> get_points() ;
            void set_points(std::vector<mt_cad::Node> nodes) ;
            static const int max_nodes;
            static const mt_cad::Materials_t material;
        private:
            
            bool triPoint(float x1, float y1, float x2, float y2, float x3, float y3,
            float px, float py);
      
          
    };
    
} ;
