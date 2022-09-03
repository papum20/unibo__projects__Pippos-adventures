//// LISTA DEI FRAME DI UN'ANIMAZIONE



#ifndef ANIMATION_HPP
#define ANIMATION_HPP


#include <iostream>
#include "coordinate.hpp"


#define ANIMATION_WIDTH 15
#define ANIMATION_HEIGHT 15
#define ANIMATION_AREA (ANIMATION_WIDTH * ANIMATION_HEIGHT)



class Animation {
	public:
		char state[ANIMATION_AREA];	//un frame dell'animazione
		Coordinate size;
		Animation *next;

		Animation();
		Animation(const char state[ANIMATION_HEIGHT][ANIMATION_WIDTH], const Coordinate size);								//inizializza singolo frame
		Animation(const char animation[][ANIMATION_HEIGHT][ANIMATION_WIDTH], const Coordinate size, const int len);			//inizializza intera lista (lunghezza len)
		Animation *tail_insert(Animation *head, const char state[ANIMATION_HEIGHT][ANIMATION_WIDTH], Coordinate size);
		void delete_list();
};

typedef Animation *p_Animation;


#endif