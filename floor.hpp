#ifndef FLOOR_HPP
#define FLOOR_HPP


#include "inanimate.hpp"



class Floor : public Inanimate {
	private:

	public:
		Floor();

		void drawAtPosition(pMap map, Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate win_size, Coordinate pos);
};

typedef Floor *pFloor;



#endif