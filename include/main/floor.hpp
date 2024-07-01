#ifndef FLOOR_HPP
#define FLOOR_HPP


#include "main/fixed.hpp"



class Floor : public Fixed {
	private:

	public:
		Floor();

		void drawAtPosition(pMap map, Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate win_size, Coordinate pos);
};

typedef Floor *pFloor;



#endif