#include "main/inanimate.hpp"


Inanimate::Inanimate() : Physical() {

}

void Inanimate::drawCell(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate pos, attr_t color) {
	char c = -1;
	if(scr[pos.rel_int_y()][pos.rel_int_x()].getCh() == CHAR_OUTSIDE) c = CHAR_EMPTY;
	scr[pos.rel_int_y()][pos.rel_int_x()].edit(c, -1, color, CELL_NO_ATTR);
}


void Inanimate::drawAtPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate win_size, Coordinate pos) {
	pos.setBounds(win_start, Coordinate(win_start, win_size));
	drawCell(scr, pos, main_color);
}