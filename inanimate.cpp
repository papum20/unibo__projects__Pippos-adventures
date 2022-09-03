#include "inanimate.hpp"


Inanimate::Inanimate() : Physical() {

}

void Inanimate::drawCell(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate pos, attr_t color) {
	scr[(int)pos.relative_y()][(int)pos.relative_x()].edit(-1, -1, color, -1);
}
void Inanimate::drawAtPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate win_size, Coordinate pos) {
	if(scr[pos.inty()][pos.intx()].getCh() == CHAR_EMPTY) drawCell(scr, pos, main_color);
	else drawCell(scr, pos, second_color);
	drawn = true;
}