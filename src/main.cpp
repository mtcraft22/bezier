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

#include <cstdlib>
#include <mtcad/mtcad.hpp>
#include <GUI/ImageButton.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
int gridsize = 20 ;
const int ticksframe = 1000/60;
int canvas_y_coord = 0;

int main(int argc, char **argv){

   
    int psw , psh;
    int sw,sh;

    SDL_GetWindowSize(window, &sw, &sh);
    canvas_y_coord = sh/4;
    SDL_Texture * canvas = SDL_CreateTexture(ctx, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, sw, sh);
    int ideal = 0;
    for (int i= 0; i <= gridsize;i++){
        if ((canvas_y_coord + i) % gridsize == 0){
            ideal = canvas_y_coord + i;
        }
    }
    SDL_Texture * gui = SDL_CreateTexture(ctx,SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,sw, ideal);
   



   
    render_grid(sw, sh, canvas);
    
    Uint32 * pixels2;
    int pitch2;

        SDL_LockTexture(gui, NULL, (void **)&pixels2, &pitch2);
        for (int y = 0; y<ideal; y++){
            for (int x = 0; x<sw; x++) {
        
                    pixels2[y*sw+x] = 0x0000330f;
                
                
            }
        }
        SDL_UnlockTexture(gui);
   
    //mt_cad::Curve Curv = mt_cad::Curve(  nodes  );
    int end,start = SDL_GetTicks(); 
    double delta = 0.0;
    bool run = true;

    std::vector<mt_cad::Shape *> shapes;

    

    SDL_Event e;
    
    bool draggin = false;
    bool innode = false;
    bool creating = false;
    std::string material = "";
    int mx,my = 0;

    int sel = 0;
    int selnode = 0;

    
	while (run) {
        
        start = SDL_GetTicks();
        delta = start-end;
        if ( delta > ticksframe){
            end = start;
            
            SDL_SetRenderDrawColor(ctx, 55, 55, 55,255);
            SDL_RenderClear(ctx);
            SDL_SetRenderDrawColor(ctx,255, 255, 255, 255);
            psw = sw;
            psh = sh;
            SDL_GetWindowSize(window, &sw, &sh);
            
            SDL_Rect  dest = {0,0,sw,sh};
            SDL_RenderCopy(ctx, canvas, NULL, &dest);

           
            
            if (shapes.size() > 0){
            for ( int i = 0; i < shapes.size(); i++ ){
                
                shapes.at(i)->draw(ctx);
            }
            for (int i = 0; i< shapes.at(sel)->get_points().size(); i++){
                SDL_SetRenderDrawColor(ctx, 255, 0, 0,255);
                shapes.at(sel)->get_points().at(i).draw(ctx);
                if(draggin && shapes.at(sel)->get_points().at(i).hover(mx, my) ){
                    
                    shapes.at(sel)->get_points().at(i).set_coords(gridsize*(mx/gridsize), gridsize*(my/gridsize));
                }
                SDL_SetRenderDrawColor(ctx,255, 255, 255, 255);
            }
            SDL_SetRenderDrawColor(ctx,255, 0, 0, 255);
            //Curv.draw(ctx);
            }
            while (SDL_PollEvent(&e)) {
                
                if (e.type == SDL_QUIT) {
                    run = false;
                }
                if (e.type == SDL_WINDOWEVENT){
                    if (e.window.event == SDL_WINDOWEVENT_RESIZED){
                        
                        psw = sw;
                        psh = sh;
                        int pideal = ideal;
                        SDL_GetWindowSize(window, &sw, &sh);
                        SDL_DestroyTexture(canvas);
                        canvas = SDL_CreateTexture(ctx, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, sw, sh);

                        render_grid(sw, sh, canvas);
                        canvas_y_coord = sh/4;
                        if (shapes.size() > 0){
                            for (int i= 0; i <= gridsize;i++){
                                if ((canvas_y_coord + i) % gridsize == 0){
                                    ideal = canvas_y_coord + i;
                                }
                            }
                            for ( int i = 0; i < shapes.size(); i++ ){
                            for (int i2 = 0; i2< shapes.at(i)->get_points().size(); i2++){
                                        std::vector<mt_cad::Node> nodes = shapes.at(i)->get_points();
                                        int x,y ;
                                        Restictions res =  nodes.at(i2).get_canmove();
                                        nodes.at(i2).set_canmove(XY);
                                        nodes.at(i2).get_coords(x, y);
                                        
                                        nodes.at(i2).set_coords(x,y + (ideal-pideal));
                                        nodes.at(i2).set_canmove(res);
                                        shapes.at(i)->set_points( nodes);
                                    }
                                }
                        
                        }
                    }
                    
                }
                if(e.type == SDL_MOUSEBUTTONDOWN){
                    if (shapes.size() > 0){
                    if(!draggin){
                        for ( int x = 0; x < shapes.size(); x++ ){
                            if (shapes.at(x)->hover(mx, my)){
                                sel = x;
                                break;
                            }
                        }       
                    }
                    draggin = true;}
                }
                if(e.type == SDL_MOUSEBUTTONUP){
                    draggin = false;
                    innode = false;
                     
                }
                if(e.type == SDL_MOUSEMOTION){
                 
                    mx = e.motion.x;
                    my = e.motion.y;
                    
                    if (draggin ){
                        if (!innode){
                            if (shapes.size() > 0){
                            for (int i = 0; i< shapes.at(sel)->get_points().size(); i++){
                                if(draggin && shapes.at(sel)->get_points().at(i).hover(mx, my) ){
                                    std::vector<mt_cad::Node> nodes = shapes.at(sel)->get_points();
                                    nodes.at(i).set_coords(gridsize * (std::trunc(mx/gridsize)),(gridsize * (std::trunc(my/gridsize))));
                                    shapes.at(sel)->set_points( nodes);
                                    selnode = i;
                                    innode = true;
                                    if (i == 0){
                                        for (int i = 1; i< shapes.at(sel)->get_points().size(); i++){
                                            std::vector<mt_cad::Node> nodes = shapes.at(sel)->get_points();
                                            int x,y ;
                                            nodes.at(i).get_coords(x, y);
                                            
                                            nodes.at(i).set_coords(x + e.motion.xrel,y + e.motion.yrel);
                                            shapes.at(sel)->set_points( nodes);
                                            
                                        }
                                    }
                                    break;
                            }}
                        }
                        }else if (draggin) {
                            if (shapes.size() > 0){
                                std::vector<mt_cad::Node> nodes = shapes.at(sel)->get_points();
                                nodes.at(selnode).set_coords(gridsize * (std::trunc(mx/gridsize)),(gridsize * (std::trunc(my/gridsize))));

                                shapes.at(sel)->set_points( nodes);
                                if (selnode == 0){
                                    for (int i = 1; i< shapes.at(sel)->get_points().size(); i++){
                                        std::vector<mt_cad::Node> nodes = shapes.at(sel)->get_points();
                                        int x,y ;
                                        nodes.at(i).get_coords(x, y);
                                        nodes.at(i).set_coords(x + e.motion.xrel,y + e.motion.yrel);
                                        shapes.at(sel)->set_points( nodes);
                                    }
                                }
                            }
                            
                        }
                        
                      
                    
                    }
                }

            } 
            SDL_DestroyTexture(gui);
            gui = SDL_CreateTexture(ctx, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, sw, ideal);

            
            SDL_Rect  dest2 = {0,0,sw,ideal};

            SDL_LockTexture(gui, NULL, (void **)&pixels2, &pitch2);
            for (int y = 0; y<ideal; y++){
                for (int x = 0; x<sw; x++) {
            
                        pixels2[y*sw+x] = 0x0000330f;
                    
                    
                }
            }
            SDL_UnlockTexture(gui);
            SDL_RenderCopy(ctx, gui, NULL, &dest2);
            
            SDL_RenderPresent(ctx);
            
            
        }else{
            SDL_Delay(ticksframe -delta);
        }

    }
    SDL_DestroyTexture(canvas);
    SDL_DestroyTexture(gui);
    SDL_DestroyRenderer(ctx);
    for (auto &s  : shapes){
        delete s;
    }
    shapes.clear();
    SDL_Quit();
    return 0;
}