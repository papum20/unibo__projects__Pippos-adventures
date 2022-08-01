//// OGGETTO "FISICO", OVVERO CHE VIENE DISEGNATO NEL LIVELLO E CHE OCCUPA UNA DETERMINATA POSIZIONE
//// COMPRENDE PERSONAGGI (CHARACTER, INCLUSI NEMICI E PLAYER), ARMI E PROIETTILI, OGGETTI INANIMATI (FLOOR, WALL, DOOR) E ITEM



#ifndef PHYSICAL_HPP
#define PHYSICAL_HPP


#include <iostream>
#include "animation.hpp"

#define ctrl(x) (x & 0x1F)				//permette di fare i controlli per le combinazioni ctrl+tasto per fare combo e simili.  
										//Es. if ( input==ctrl(a) ) permette di controllare se abbiamo premuto ctrl+a


#pragma region PHYSICAL_CONSTANTS

#define MAX_ANIMATION 6		//numero di animazioni

// ID
#pragma region PHYSICAL_IDS
#define ID_INANIMATE_S 10
#define ID_INANIMATE_E 19

#define ID_DEFAULT 0
//#define ID_PLACEHOLDER 1
#define ID_PLAYER 2
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

#pragma region PHYSICAL_STATS
#define PHYSICAL_MAX_SPEED 5.
#pragma endregion PHYSICAL_STATS

#pragma endregion PHYSICAL_CONSTANTS


#include "cell.hpp"
#include "coordinate.hpp"
#include "definitions.hpp"



class Physical {
	protected:
		Coordinate pos;		//posizione nella stanza (considerando la cella più in basso a sinistra dell'oggetto)
		Coordinate size;	//dimensioni "proiettate sul pavimeto" (larghezza * profondità)
		int id;				//intero che identifica il tipo di oggetto (comune a tutti e soli gli oggetti della stessa classe)

		p_Animation animation[MAX_ANIMATION]; //array di liste di animazioni: ogni elemento dell'array è una lista (circolare) con tutti i frame di una determinata animazione

	public:
		Physical();
		void destroy();
		void drawAtPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate pos);	//disegna l'oggetto nella finestra, alle date coordinate, secondo la sua animazione, entro i limiti della finestra
		void drawAtOwnPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start);				//disegna l'oggetto nella finestra, nella sua posizione, secondo la sua animazione, entro i limiti della finestra

		// BOOL
		bool isInanimate();
		//bool isPlaceholder();

		// GET
		int getId();
		Coordinate getPosition();
		Coordinate getSize();
		Coordinate getSpeed();				//velocità in caselle/secondo (float)
		Coordinate lastFrameMovement();		//movimento avvenuto dall'ultimo frame
};

typedef Physical *pPhysical;




#endif