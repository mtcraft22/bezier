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

#pragma once
#include "GUI/ImageButton.hpp"
#include "SDL_app.hpp"
#include "mtcad/Shape.hpp"
#include <vector>
#define IDDLE = 0b0001;
#define DRAGGIN = 0b1000;
#define INNODE = 0b0100;
#define CREATING  = 0b0010;
namespace App {
    class Bezier {
        private:
            std::vector<mt_cad::Shape> shapes;
            std::vector<GUI::ImageButton> shape_creation_buttons;
            SDL_Texture * gui;
            SDL_Texture * canvas;
            int drawing_state;
            int sel;
            int gridsize;
            SDL_app application;
        public:
            Bezier();
            void render_grid(int sw,int sh);
            int get_gridsize() ;
            std::vector<mt_cad::Shape> get_shapes() ;
            std::vector<GUI::ImageButton> get_shape_creation_buttons() ;
            SDL_Texture* get_gui() ;
            SDL_Texture* get_canvas() ;
            int get_drawing_state() ;
            int get_sel() ;

            void set_gridsize(int gridsize);
            void set_shapes(std::vector<mt_cad::Shape> shapes);
            void set_shape_creation_buttons(std::vector<GUI::ImageButton> shape_creation_buttons);
            void set_gui(SDL_Texture* gui);
            void set_canvas(SDL_Texture* canvas);
            void set_drawing_state(int drawing_state);
            void set_sel(int sel);

            ~Bezier();

    };
}