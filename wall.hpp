#ifndef WALL_HPP
#define WALL_HPP

#include "inanimate.hpp"



#define WALL_HEIGHT 4


//viene creato un solo muro e usato un puntatore allo stesso muro per disegnarlo (nelle classi level/room)


class Wall : public Inanimate {
	private:
		int top_color;
		int height;

	public:
		Wall();

		void drawAtPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate pos);	//overridden

};




#endif