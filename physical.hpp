#ifndef PHYSICAL_HPP
#define PHYSICAL_HPP


#include <iostream>
/*
#define ctrl(x) (x & 0x1F)				//permette di fare i controlli per le combinazioni ctrl+tasto per fare combo e simili.  
										//Es. if ( input==ctrl(a) ) permette di controllare se abbiamo premuto ctrl+a
*/

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
#define ID_PLAYER 2
#define ID_WALL 10
#define ID_FLOOR 11
#define ID_DOOR 20
#define ID_ARTEFACT 30
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

#pragma region PHYSICAL_STATS
#define PHYSICAL_MAX_SPEED 5.
#pragma endregion PHYSICAL_STATS

#pragma endregion PHYSICAL_CONSTANTS


#include "cell.hpp"
#include "coordinate.hpp"
#include "definitions.hpp"



class Physical {
	protected:
		Coordinate pos;
		Coordinate size;
		int id;		//intero che identifica il tipo di oggetto (comune a tutti e soli gli oggetti della stessa classe)

		p_Animation animations[MAX_ANIMATION]; //array di liste di array bidimensionali
		int current_animation;

		p_Animation tail_insert(p_Animation head, const char state[ANIMATION_HEIGHT][ANIMATION_WIDTH], int width, int height);

	public:
		Physical();
		//virtual void update(pPhysical map[], char input);
		virtual void destroy();

		void drawAtPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate pos);	//disegna l'oggetto nella finestra, alle date coordinate, secondo la sua animazione, entro i limiti della finestra
		void drawAtOwnPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start);				//disegna l'oggetto nella finestra, nella sua posizione, secondo la sua animazione, entro i limiti della finestra

		// BOOL
		bool isInanimate();
		bool isPlaceholder();

		// GET
		pPhysical checkPosition(Physical *map[], Coordinate pos);				//ritorna un puntatore all'oggetto fisico presente nella casella x,y (NULL se non presente niente)
		pPhysical checkLine(Physical *map[], Coordinate start, Coordinate end);	//checkPosition per una linea da start a end (incluso)
		int getId();
		Coordinate getPosition();
		Coordinate getSize();
		Coordinate getSpeed();				//velocità in caselle/secondo (float)
		Coordinate lastFrameMovement();
		void conflicts();
};

typedef Physical *pPhysical;




#endif