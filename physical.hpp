#ifndef PHYSICAL_HPP
#define PHYSICAL_HPP


#include <iostream>


#pragma region PHYSICAL_CONSTANTS
#pragma region PHYSICAL_ANIMATIONS
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

const int MAX_ANIMATION = 6;

#pragma endregion PHYSICAL_ANIMATIONS

// ID
#pragma region PHYSICAL_IDS
#define ID_INANIMATE_S 10
#define ID_INANIMATE_E 19

#define ID_DEFAULT 0
#define ID_PLACEHOLDER 1
#define ID_WALL 10
#define ID_FLOOR 11
#define ID_DOOR 20
#pragma endregion PHYSICAL_IDS

//// COSTANTI PER LA RAPPRESENTAZIONE GRAFICA
#pragma region GRAPHICS
// COLORI
#define COLOR_WALL COLOR_RED
#define COLOR_TRANSPARENT COLOR_YELLOW	//per il muro quando diventa più chiaro se c'è qualcosa dietro
#define COLOR_UPPER_WALL COLOR_BLACK	//bordo superiore muro
#define COLOR_FLOOR COLOR_GREEN
#define COLOR_SHADOW COLOR_CYAN			//per il pavimento con l'ombra di un oggetto
// CARATTERI
#define CHAR_EMPTY ' '

//const int wallColors[5] = {COLOR_MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA};
//const int floorColors[5] = {COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK};
#pragma endregion GRAPHICS

#pragma endregion PHYSICAL_CONSTANTS


#include "cell.hpp"
#include "coordinate.hpp"
#include "definitions.hpp"



class Physical {
	protected:
		Coordinate pos;
		int id;		//intero che identifica il tipo di oggetto (comune a tutti e soli gli oggetti della stessa classe)

		p_Animation animation[MAX_ANIMATION]; //array di liste di array bidimensionali

		p_Animation tail_insert(p_Animation head, const char state[ANIMATION_HEIGHT][ANIMATION_WIDTH], int width, int height);

	public:
		Physical();
		void destroy();
		void drawAtPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate pos);	//disegna l'oggetto nella finestra, alle date coordinate, secondo la sua animazione, entro i limiti della finestra
		void drawAtOwnPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start);				//disegna l'oggetto nella finestra, nella sua posizione, secondo la sua animazione, entro i limiti della finestra

		// BOOL
		bool isInanimate();
		bool isPlaceholder();

		// GET
		int getId();
		Coordinate getPosition();
		Coordinate lastFrameMovement();
};

typedef Physical *pPhysical;




#endif