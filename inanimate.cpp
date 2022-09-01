#include "inanimate.hpp"


Inanimate::Inanimate() : Physical() {

}

void Inanimate::init_colors() {

}

void Inanimate::drawCell(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate pos, attr_t color) {
	pos.setFullMatrix(win_start, COORDINATE_ERROR);
	if(pos.inOwnBounds())
		scr[(int)pos.relative_x()][(int)pos.relative_y()].edit(-1, -1, color, -1);
}
void Inanimate::drawAtPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate pos) {
	if(scr[pos.inty()][pos.intx()].getCh() == CHAR_EMPTY) drawCell(scr, win_start, pos, main_color);
	else drawCell(scr, win_start, pos, second_color);
}