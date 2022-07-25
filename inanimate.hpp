//classe parent di oggetti inanimati: wall, floor



#ifndef INANIMATE_HPP
#define INANIMATE_HPP


#include "physical.hpp"



class Inanimate : public Physical {
	protected:
		attr_t main_color;
		attr_t second_color;
		
		void drawCell(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate pos, attr_t color);	//riempie una cella
		
	public:
		Inanimate();
		void init_colors();

		void drawAtPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate pos);			//overridden
};

typedef Inanimate *pInanimate;



#endif