#ifndef FLOOR_HPP
#define FLOOR_HPP


#include "inanimate.hpp"







class Floor : public Inanimate {
	private:

	public:
		Floor();

		void drawAtPosition(chtype scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_size, Coordinate pos);	//overridden

};



#endif