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

#include <SDL2/SDL.h>
namespace App {
    class SDL_app {
        public:
            SDL_app();
            SDL_Window* get_window();
            SDL_Renderer* get_ctx();
            int get_maxFrames();
            void get_windowSize(int &w , int &h);
            void set_maxFrames(int frames);
            ~SDL_app();
        private:
            SDL_Window * window;
            SDL_Renderer  * ctx;
            int frames;
            int framerateTiming;
            
    };
} ;
