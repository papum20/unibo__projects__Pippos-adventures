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


// ID
#define INANIMATE_ID_S 10
#define INANIMATE_ID_E 19

#define DEFAULT_ID 0
#define WALL_ID 10
#define FLOOR_ID 11



const int MAX_ANIMATION = 6;

class Physical {
	protected:
		int xPos;
		int yPos;
		int id;		//intero che identifica il tipo di oggetto (comune a tutti e soli gli oggetti della stessa classe)

		p_Animation animation[MAX_ANIMATION]; //array di liste di array bidimensionali

		p_Animation tail_insert(p_Animation head, const char state[][ANIMATION_WIDTH], int width, int height);
	public:
		Physical();
		void drawAtPosition(chtype scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_size, Coordinate pos);	//disegna l'oggetto nella finestra, alle date coordinate, secondo la sua animazione, entro i limiti della finestra
		void drawAtOwnPosition(chtype scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_size);					//disegna l'oggetto nella finestra, nella sua posizione, secondo la sua animazione, entro i limiti della finestra

		// BOOL
		bool isInanimate();

		// GET
		int getId();
		void getPosition(Coordinate &out);
};

typedef Physical *pPhysical;




#endif PHYSICAL_HPP