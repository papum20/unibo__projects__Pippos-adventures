#include "floor.hpp"



Floor::Floor() : Inanimate() {
	id = ID_FLOOR;

	main_color = COLOR_FLOOR;
	second_color = COLOR_SHADOW;
}

void Floor::drawAtPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate pos) {
	if(scr[pos.y][pos.x].getCh() == CHAR_EMPTY) Inanimate::drawAtPosition(scr, win_start, pos, main_color);
	else Inanimate::drawAtPosition(scr, win_start, pos, second_color);
}