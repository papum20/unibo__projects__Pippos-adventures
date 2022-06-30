#include "wall.hpp"



Wall::Wall() : Inanimate() {
	id = WALL_ID;
	height = WALL_HEIGHT;

	main_color = COLOR_WALL;
	second_color = COLOR_TRANSPARENT;
}


void Floor::drawAtPosition(chtype scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_size, Coordinate pos) {
	
}