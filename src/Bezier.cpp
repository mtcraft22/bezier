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
#include <Bezier.hpp>
#include <SDL2/SDL_render.h>


App::Bezier::Bezier(){
    
}
void App::Bezier::render_grid(int sw,int sh){
        Uint32 * pixels;
        int pitch;
        SDL_LockTexture(canvas, NULL, (void **)&pixels, &pitch);
        for (int y = 0; y<sh; y++){
            for (int x = 0; x<sw; x++) {
        
                if (!(x%gridsize) && !(y%gridsize)){
                   
                    pixels[y*sw+x] = 0xffffff0f;
                }else{
                    pixels[y*sw+x] = 0x0000180f;
                }
                
            }
        }
        SDL_UnlockTexture(canvas);
    }
App::Bezier::~Bezier(){
    SDL_DestroyTexture(this->canvas);
    SDL_DestroyTexture(this->gui);
}