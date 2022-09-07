#ifndef WALL_HPP
#define WALL_HPP

#include "inanimate.hpp"



#define WALL_HEIGHT 5


class Wall : public Inanimate {
	private:
		int base_color;
		int top_color;
		int height;

	protected:
		void drawCell(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate pos, attr_t color);	//riempie una cella

	public:
		Wall();

		void drawAtPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate win_size, Coordinate pos);
		//precondizione: da richiamare con coordinate giuste

};

typedef Wall *pWall;




#endif