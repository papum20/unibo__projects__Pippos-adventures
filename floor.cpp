#include "floor.hpp"
#include "map_handler.hpp"



Floor::Floor() : Inanimate() {
	id = ID_FLOOR;

	main_color = COLOR_FLOOR;
	second_color = COLOR_SHADOW;
}



void Floor::drawAtPosition(pMap map, Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate win_size, Coordinate pos) {
	pos.setBounds(win_start, Coordinate(win_start, win_size));
	if(MapHandler::checkPosition(map, pos) != NULL) drawCell(scr, pos, second_color);
	else drawCell(scr, pos, main_color);
}
		
