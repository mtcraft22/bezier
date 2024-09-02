#include "Node.hpp"
#include "Rectangle.hpp"
#include "Shape.hpp"
#include "Triangle.hpp"
#include "circle.hpp"
#include "curve.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <vector>

int gridsize = 20 ;
const int ticksframe = 1000/60;
void render_grid(int sw,int sh,SDL_Texture *  canvas){
        Uint32 * pixels;
        int pitch;
        SDL_LockTexture(canvas, NULL, (void **)&pixels, &pitch);
        for (int y = 0; y<sh; y++){
            for (int x = 0; x<sw; x++) {
        
                if (!(x%gridsize) && !(y%gridsize)){
                    
                    pixels[y*sw+x] = 0xffff00ff;
                }
            }
        }
        SDL_UnlockTexture(canvas);
    }
int main(int argc, char **argv){
    if(SDL_Init(SDL_INIT_EVERYTHING)<0){
        std::cout << SDL_GetError() << std::endl;
        return -1;
    }
    SDL_Window * window = SDL_CreateWindow("curbas", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 720, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
    SDL_Renderer * ctx = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    int sw,sh;
    SDL_GetWindowSize(window, &sw, &sh);
    SDL_Texture * canvas = SDL_CreateTexture(ctx, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, sw, 3*(sh/4));
    SDL_Texture * gui = SDL_CreateTexture(ctx,SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,sw, sh/4);
    Uint32 * pixels;
    int pitch;
    
   
    render_grid(sw, sh, canvas);
   
   
    std::vector<mt_cad::Node> nodes3 = {{300,300,XY},{320,300,XY}};
    mt_cad::Circle tri3 = mt_cad::Circle(  nodes3  );
    std::vector<mt_cad::Node> nodes4 = {{400,400,XY},{440,440,XY}};
    mt_cad::Rectangle tri4 = mt_cad::Rectangle(  nodes4  );
    std::vector<mt_cad::Node> nodes5 = {{500,500,XY},{540,500,XY},{500,540,XY}};
    mt_cad::Triangle tri5 = mt_cad::Triangle(  nodes5  );
    std::vector<mt_cad::Node> nodes6 = {{100,100,XY},{140,100,XY},{100,140,XY}};
    mt_cad::Curve tri6 = mt_cad::Curve(  nodes6  );
    //mt_cad::Curve Curv = mt_cad::Curve(  nodes  );
    int end,start = SDL_GetTicks(); 
    double delta = 0.0;
    bool run = true;

    std::vector<mt_cad::Shape *> shapes;

    shapes.push_back(&tri6);
    shapes.push_back(&tri3);
    shapes.push_back(&tri4);
    shapes.push_back(&tri5);
    

    SDL_Event e;
    
    bool draging = false;
    bool innode = false;
    
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
            SDL_GetWindowSize(window, &sw, &sh);
            std::cout << sh << " " << sh << std::endl;
            SDL_Rect  dest = {0,(int)sh/4,sw,(int)3*(sh/4)};
            SDL_RenderCopy(ctx, canvas, NULL, &dest);
           
            
    
            for ( int i = 0; i < shapes.size(); i++ ){
                
                shapes.at(i)->draw(ctx);
            }
            for (int i = 0; i< shapes.at(sel)->get_points().size(); i++){
                
                shapes.at(sel)->get_points().at(i).draw(ctx);
                if(draging && shapes.at(sel)->get_points().at(i).hover(mx, my) ){
                    
                    shapes.at(sel)->get_points().at(i).set_coords(gridsize*(mx/gridsize), gridsize*(my/gridsize));
                }
            }
            SDL_SetRenderDrawColor(ctx,255, 0, 0, 255);
            //Curv.draw(ctx);
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    run = false;
                }
                if (e.type == SDL_WINDOWEVENT){
                    if (e.window.event == SDL_WINDOWEVENT_RESIZED){
                        SDL_GetWindowSize(window, &sw, &sh);
                        SDL_DestroyTexture(canvas);
                        canvas = SDL_CreateTexture(ctx, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, sw, 3*(sh/4));
                        render_grid(sw, 3*(sh/4), canvas);
                       
                    }
                }
                if(e.type == SDL_MOUSEBUTTONDOWN){
                    
                    if(!draging){
                        for ( int x = 0; x < shapes.size(); x++ ){
                            if (shapes.at(x)->hover(mx, my)){
                                sel = x;
                                break;
                            }
                        }       
                    }
                    draging = true;
                }
                if(e.type == SDL_MOUSEBUTTONUP){
                    draging = false;
                    innode = false;
                }
                if(e.type == SDL_MOUSEMOTION){
                 
                    mx = e.motion.x;
                    my = e.motion.y;
                    
                    if (draging ){
                        if (!innode){
                            for (int i = 0; i< shapes.at(sel)->get_points().size(); i++){
                

                            if(draging && shapes.at(sel)->get_points().at(i).hover(mx, my) ){
                                std::vector<mt_cad::Node> nodes = shapes.at(sel)->get_points();
                                nodes.at(i).set_coords(gridsize * (std::trunc(mx/gridsize)),gridsize * (std::trunc(my/gridsize)));
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
                            }
                        }
                        }else if (draging) {
                            std::vector<mt_cad::Node> nodes = shapes.at(sel)->get_points();
                            nodes.at(selnode).set_coords(gridsize * (std::trunc(mx/gridsize)),gridsize * (std::trunc(my/gridsize)));

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
            SDL_RenderPresent(ctx);
            
        }else{
            SDL_Delay(ticksframe -delta);
        }

    }
    SDL_DestroyTexture(canvas);
    SDL_DestroyTexture(gui);
    SDL_DestroyRenderer(ctx);
    SDL_Quit();
    return 0;
}