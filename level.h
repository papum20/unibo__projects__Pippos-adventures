#ifndef LEVEL_H
#define LEVEL_H

#include <curses.h>
#include "room.h"


#define LEVEL_WIDTH 135
#define LEVEL_HEIGHT 35
const short wallColors[5] = {COLOR_MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA};
const short floorColors[5] = {COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK};



class Level {
	private:
		int width;
		int height;
		short wallColor;
		short floorColor;

		int n_rooms;

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