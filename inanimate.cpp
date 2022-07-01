#include "inanimate.hpp"


Inanimate::Inanimate() : Physical() {

}

void Inanimate::init_colors() {

}

void Inanimate::drawAtPosition(chtype scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_size, Coordinate pos, attr_t color) {
	if(pos.inOwnBounds()) {
		chtype pixel = scr[pos.relative_x()][pos.relative_y()] | COLOR_PAIR();
		scr[pos.relative_x()][pos.relative_y()] = pixel;
	}
}