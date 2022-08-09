//// LISTA DEI FRAME DI UN'ANIMAZIONE



#ifndef ANIMATION_HPP
#define ANIMATION_HPP


#include <iostream>


#define ANIMATION_WIDTH 6
#define ANIMATION_HEIGHT 5



class Animation {
	public:
		char state[ANIMATION_HEIGHT][ANIMATION_WIDTH];
		int width;
		int height;
		Animation *next;

		Animation();
		Animation(const char state[ANIMATION_HEIGHT][ANIMATION_WIDTH], int width, int height);					//inizializza singolo frame
		Animation(const char animation[][ANIMATION_HEIGHT][ANIMATION_WIDTH], int width, int height, int len);	//inizializza intera lista (lunghezza len)
		Animation *tail_insert(Animation *head, const char state[ANIMATION_HEIGHT][ANIMATION_WIDTH], int width, int height);
		void delete_list();
};

typedef Animation *p_Animation;


#endif