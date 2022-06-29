#ifndef FLOOR_HPP
#define FLOOR_HPP


#include "inanimate.hpp"







class Floor : public Inanimate {
	private:

	public:
		Floor();

		void drawAtPosition(WINDOW *win, Coordinate win_size, Coordinate pos);	//overridden

};



#endif