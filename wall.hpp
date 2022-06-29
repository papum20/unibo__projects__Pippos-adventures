#ifndef WALL_HPP
#define WALL_HPP

#include "inanimate.hpp"



#define WALL_HEIGHT 4


//viene creato un solo muro e usato un puntatore allo stesso muro per disegnarlo (nelle classi level/room)


class Wall : public Inanimate {
	private:
		//color
		//char
		int height;

	public:
		Wall();

		void drawAtPosition(WINDOW *win, Coordinate win_size, Coordinate pos);	//overridden

};




#endif