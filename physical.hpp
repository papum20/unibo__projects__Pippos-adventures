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

const int MAX_ANIMATION = 6;

class Physical {
	protected:
		int xPos;
		int yPos;
		p_Animation animation[MAX_ANIMATION]; //array di liste di array bidimensionali
		p_Animation tail_insert(p_Animation head, const char state[][ANIMATION_WIDTH], int width, int height);
	public:
		Physical();
};

typedef Physical *pPhysical;




#endif PHYSICAL_HPP