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

#include "Bezier.hpp"
#include "SDL_app.hpp"
#include "mtcad/Shape.hpp"
#include <cstdlib>
#include <mtcad/mtcad.hpp>
#include <GUI/ImageButton.hpp>
#include <SDL2/SDL.h>
#include <cmath>
#include <vector>

int gridsize = 20 ;
const int ticksframe = 1000/60;


int main(int argc, char **argv){
    int end,start = SDL_GetTicks();
    double delta = 0.0;
    bool run = true;
    SDL_Event e;
    int mx,my = 0; 
    App::Bezier bezier = App::Bezier(App::SDL_app());
   
    bezier.render_grid();
    bezier.render_gui();
   
	while (run) {
        
        start = SDL_GetTicks();
        delta = start-end;
        if ( delta > ticksframe){
            end = start;
            
            SDL_SetRenderDrawColor(bezier.get_ctx(), 55, 55, 55,255);
            SDL_RenderClear(bezier.get_ctx());
            SDL_SetRenderDrawColor(bezier.get_ctx(),255, 255, 255, 255);
           
          
            bezier.render_grid();

            std::vector<mt_cad::Shape *> shapes = bezier.get_shapes();
            
            if (shapes.size() > 0){
            for ( int i = 0; i < shapes.size(); i++ ){
                
                shapes.at(i)->draw(bezier.get_ctx());
            }
            for (int i = 0; i< shapes.at(sel)->get_points().size(); i++){
                SDL_SetRenderDrawColor(bezier.get_ctx(), 255, 0, 0,255);
                shapes.at(sel)->get_points().at(i).draw(bezier.get_ctx());
                if(draggin && shapes.at(sel)->get_points().at(i).hover(mx, my) ){
                    
                    shapes.at(sel)->get_points().at(i).set_coords(gridsize*(mx/gridsize), gridsize*(my/gridsize));
                }
                SDL_SetRenderDrawColor(bezier.get_ctx(),255, 255, 255, 255);
            }
            SDL_SetRenderDrawColor(bezier.get_ctx(),255, 0, 0, 255);
            //Curv.draw(bezier.get_ctx());
            }
            while (SDL_PollEvent(&e)) {
                
                if (e.type == SDL_QUIT) {
                    run = false;
                }
                if (e.type == SDL_WINDOWEVENT){
                    if (e.window.event == SDL_WINDOWEVENT_RESIZED){
                        
                      
                        int pideal = bezier.get_ideal_y_canvas_cord();
                        bezier.render_grid();
                        
                        if (shapes.size() > 0){
                            int ideal = bezier.get_ideal_y_canvas_cord();
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
                    if((bezier.get_drawing_state() & DRAGGIN) != DRAGGIN){
                        for ( int x = 0; x < shapes.size(); x++ ){
                            if (shapes.at(x)->hover(mx, my)){
                                sel = x;
                                break;
                            }
                        }       
                    }
                    draggin = true;
                    }
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
            bezier.set_shapes(shapes);
            bezier.render_grid();
            
            SDL_RenderPresent(bezier.get_ctx());
            
            
        }else{
            SDL_Delay(ticksframe -delta);
        }

    }
    SDL_Quit();
    return 0;
}