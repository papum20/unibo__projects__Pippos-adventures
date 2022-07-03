#include "wall.hpp"



Wall::Wall() : Inanimate() {
	id = ID_WALL;
	height = WALL_HEIGHT;

	main_color = COLOR_WALL;
	second_color = COLOR_TRANSPARENT;
	top_color = COLOR_UPPER_WALL;
}


void Wall::drawAtPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate pos) {
	for(int i = 0; i < height - 1; i++)	{
		pos.y++;
		Inanimate::drawAtPosition(scr, win_start, pos);
	}
	pos.y++;
	Inanimate::drawCell(scr, win_start, pos, top_color);
}