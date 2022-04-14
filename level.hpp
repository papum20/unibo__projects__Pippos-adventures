#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <curses.h>
#include "room.hpp"


#define CAMERA_WIDTH 135
#define CAMERA_HEIGHT 35
#define N_ROOMS 10

//const short wallColors[5] = {COLOR_MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA};
//const short floorColors[5] = {COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK};



class Level {
	private:
		//dimensioni dello schermo disponibile, ovvero della parte di stanza disegnata a schermo
		int width;
		int height;
		//short wallColor;
		//short floorColor;

		//int n_rooms;
		pRoom curRoom;
		

	public:
		Level();			//costruttore
		draw();				//disegna livello (chiamato a ogni frame, se non in pausa)
		generateRoom();
		//genera una stanza (come array bidimensionale)
		//generateAll();
		//genera tutte le stanze

		//ANIMAZIONI
		//player
		void playerUpAnimation();
		void playerRightAnimation();
		void playerDownAnimation();
		void playerLeftAnimation();
};



#endif