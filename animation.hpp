//// LISTA DEI FRAME DI UN'ANIMAZIONE



#ifndef ANIMATION_HPP
#define ANIMATION_HPP


#include <iostream>
#include "coordinate.hpp"


#define ANIMATION_WIDTH 15
#define ANIMATION_HEIGHT 15
const Coordinate ANIMATION_SIZE = Coordinate(ANIMATION_WIDTH, ANIMATION_HEIGHT);
#define ANIMATION_AREA (ANIMATION_WIDTH * ANIMATION_HEIGHT)
#define ANIMATION_FIRST_INDEX 0



class Animation {
	private:
		void set(const char state[ANIMATION_HEIGHT][ANIMATION_WIDTH], const Coordinate size, Animation *next = NULL);		//setup
		void setSingle(const char state[ANIMATION_AREA], const Coordinate size, Animation *next = NULL);					//setup
		void tail_insertSingle(const char state[ANIMATION_AREA], Coordinate size);											//inserisce in coda (rispetto alla testa attuale/passata per parametro)

	public:
		char state[ANIMATION_AREA];		//un frame dell'animazione
		int index;						//indice del frame: indica l'ordine (da 0 all'ultimo)
		Coordinate size;
		Animation *next;

		Animation();
		Animation(const char state[ANIMATION_HEIGHT][ANIMATION_WIDTH], const Coordinate size);							//inizializza singolo frame
		Animation(const char animation[ANIMATION_AREA], const Coordinate);												//inizializza intera lista (lunghezza len)
		Animation(const char animation[][ANIMATION_HEIGHT][ANIMATION_WIDTH], const Coordinate size, const int len);		//inizializza intera lista (lunghezza len)
		void copy(Animation *B);
		void tail_insert(const char state[ANIMATION_HEIGHT][ANIMATION_WIDTH], Coordinate size);							//inserisce in coda (rispetto alla testa attuale/passata per parametro)
		void delete_list();

		char at(Coordinate pos);		//carattere in posizione pos (dal basso)
		bool isLastFrame();				//se è l'ultimo frame dell'animazione
		bool isFirstFrame();
};

typedef Animation *p_Animation;


#endif