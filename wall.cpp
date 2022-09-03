#include "wall.hpp"



Wall::Wall() : Inanimate() {
	id = ID_WALL;
	height = WALL_HEIGHT;

	main_color = COLOR_WALL;
	second_color = COLOR_TRANSPARENT;
	top_color = COLOR_UPPER_WALL;
}


void Wall::drawAtPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate win_size, Coordinate pos) {
	for(int i = 0; i < height - 1; i++)	{
		Inanimate::drawAtPosition(scr, win_start, win_size, pos);
		pos.y++;
	}
	Inanimate::drawCell(scr, pos, top_color);
}