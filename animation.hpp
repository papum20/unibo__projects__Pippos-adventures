//// LISTA DEI FRAME DI UN'ANIMAZIONE



#ifndef ANIMATION_HPP
#define ANIMATION_HPP


#include <iostream>
#include "coordinate.hpp"


#define ANIMATION_WIDTH 15
#define ANIMATION_HEIGHT 15
#define ANIMATION_AREA (ANIMATION_WIDTH * ANIMATION_HEIGHT)
#define ANIMATION_FIRST_INDEX 0



class Animation {
	public:
		char state[ANIMATION_AREA];		//un frame dell'animazione
		int index;						//indice del frame: indica l'ordine (da 0 all'ultimo)
		Coordinate size;
		Animation *next;

		Animation();
		Animation(const char state[ANIMATION_HEIGHT][ANIMATION_WIDTH], const Coordinate size);							//inizializza singolo frame
		Animation(const char animation[][ANIMATION_HEIGHT][ANIMATION_WIDTH], const Coordinate size, const int len);		//inizializza intera lista (lunghezza len)
		Animation *tail_insert(Animation *head, const char state[ANIMATION_HEIGHT][ANIMATION_WIDTH], Coordinate size);	//inserisce in coda (rispetto alla testa attuale/passata per parametro)
		void delete_list();
		bool isLastFrame();				//se è l'ultimo frame dell'animazione
};

typedef Animation *p_Animation;


#endif