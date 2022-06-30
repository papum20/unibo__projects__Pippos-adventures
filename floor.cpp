#include "floor.hpp"



Floor::Floor() : Inanimate() {
	id = FLOOR_ID;

	main_color = COLOR_FLOOR;
	second_color = COLOR_SHADOW;
}

void Floor::drawAtPosition(chtype scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_size, Coordinate pos) {
	
}