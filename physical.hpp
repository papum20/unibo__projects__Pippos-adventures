#ifndef PHYSICAL_HPP
#define PHYSICAL_HPP

#include <iostream>
#include "room.hpp"

const int ANIMATION_WIDTH = 6;
const int ANIMATION_HEIGHT = 5;
//struttura della lista degli array dell'animazione del player
struct Animation{
	char state[ANIMATION_HEIGHT][ANIMATION_WIDTH];
	Animation *next;
	int height;
	int width;
};
typedef Animation *p_Animation;


#define DEFAULT_ID 0
#define WALL_ID 10
#define FLOOR_ID 11
#define PLAYER_ID 20




const int MAX_ANIMATION = 9;

class Physical {
	protected:
		int xPos;
		int yPos;
		int id;		//intero che identifica il tipo di oggetto (comune a tutti e soli gli oggetti della stessa classe)

		p_Animation animation[MAX_ANIMATION]; //array di liste di array bidimensionali
		p_Animation tail_insert(p_Animation head, const char state[][ANIMATION_WIDTH], int width, int height);
	public:
		Physical();
		void drawAtPosition(WINDOW *win, Coordinate win_size, Coordinate pos);	//disegna l'oggetto nella finestra, alle date coordinate, secondo la sua animazione, entro i limiti della finestra
		void drawAtPosition(WINDOW *win, Coordinate win_size);					//disegna l'oggetto nella finestra, nella sua posizione, secondo la sua animazione, entro i limiti della finestra

		// GET
		void getPosition(Coordinate &out);
		int getId();
};

typedef Physical *pPhysical;




#endif PHYSICAL_HPP