#pragma once
#include <SDL2/SDL.h>
typedef enum rectitions {XY,X,Y} Restictions ;
namespace mt_cad{
	class Node{
		public:
			Node(int x, int y, Restictions res);
			void draw(SDL_Renderer *ctx);
			void get_coords(int &x, int &y);
			void set_coords(int x,int y);
			Restictions get_canmove();
			void set_canmove(Restictions canmove);
			bool hover(int x, int y);
		private:
			Restictions canmove;
			int x,y;
		};
}
