#ifndef PHYSICAL_HPP
#define PHYSICAL_HPP

#include <iostream>

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
#define ID_INANIMATE_S 10
#define ID_INANIMATE_E 19

#define ID_DEFAULT 0
#define ID_PLACEHOLDER 1
#define ID_WALL 10
#define ID_FLOOR 11

const int MAX_ANIMATION = 6;


#include "cell.hpp"
#include "level.hpp"



class Physical {
	protected:
		int xPos;
		int yPos;
		int id;		//intero che identifica il tipo di oggetto (comune a tutti e soli gli oggetti della stessa classe)

		p_Animation animation[MAX_ANIMATION]; //array di liste di array bidimensionali

		p_Animation tail_insert(p_Animation head, const char state[][ANIMATION_WIDTH], int width, int height);
	public:
		Physical();
		void drawAtPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate pos);	//disegna l'oggetto nella finestra, alle date coordinate, secondo la sua animazione, entro i limiti della finestra
		void drawAtOwnPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start);				//disegna l'oggetto nella finestra, nella sua posizione, secondo la sua animazione, entro i limiti della finestra

		// BOOL
		bool isInanimate();
		bool isPlaceholder();

		// GET
		int getId();
		Coordinate getPosition();
};

typedef Physical *pPhysical;




#endif