#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_ttf.h>
#include <atomic>
#include <mutex>
#include <string>
#include <thread>
typedef struct event_listener:public std::mutex{
	SDL_Event e;
}Event_listener;
namespace GUI {
	class Boton{
			
		protected:
			std::mutex state;
			Event_listener el;
			
			int w,h;
			int gapX, gapY;
			SDL_Rect* box;
			SDL_Color color;
			SDL_Color colortext;
			
			bool pressed, hover;
			std::string text;
		
			int x, y;
			std::thread hilo;
			void check_status();
			std::atomic<bool> stop;
		public:
			void (*on_hover)(void);
			void (*on_click)(void);
			void (*on_hover_release)(void);
			Boton(int x,int y,int gapX,int gapY, SDL_Color color, SDL_Color colortext,std::string text,SDL_Event* e);
			void set_evento(SDL_Event* e);
			void getGap(int* gapX, int* gapY);
			void setGap(int gapX, int gapY);
			void getPos(int* x, int* y);
			void setPos(int x, int y);
			void getColor(SDL_Color* color, SDL_Color* colortext);
			void setColor(SDL_Color color, SDL_Color colortext);
			void render(SDL_Renderer* ctx, TTF_Font* font, SDL_Color* srccolor);
			bool Is_clicked();
			bool Is_hover();
			~Boton();
	};
}
