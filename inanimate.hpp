////CLASSE PARENT DI OGGETTI INANIMATI : wall, floor, door



#ifndef INANIMATE_HPP
#define INANIMATE_HPP


#include "physical.hpp"



class Inanimate : public Physical {
	protected:
		attr_t main_color;
		attr_t second_color;
		
		void drawCell(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate pos, attr_t color);	//riempie una cella
		//precondizione: da richiamare con coordinate giuste
		
	public:
		Inanimate();

		virtual void drawAtPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate win_size, Coordinate pos);
		//precondizione: da richiamare con coordinate giuste
};

typedef Inanimate *pInanimate;



#endif