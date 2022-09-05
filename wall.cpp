#include "wall.hpp"



Wall::Wall() : Inanimate() {
	id = ID_WALL;
	height = WALL_HEIGHT;

	main_color = COLOR_WALL;
	second_color = COLOR_TRANSPARENT;
	top_color = COLOR_UPPER_WALL;
}


void Wall::drawAtPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate win_size, Coordinate pos) {
	Coordinate win_end = Coordinate(win_start, win_size);
	Coordinate i = Coordinate(pos, win_start, win_end);
	while(i.y - pos.y < height && i.y < win_end.y) {
		if(i.y < height - 1) Inanimate::drawAtPosition(scr, win_start, win_size, i);
		else Inanimate::drawCell(scr, i, top_color);
		i.y++;
	}
}