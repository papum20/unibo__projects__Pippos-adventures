#include "wall.hpp"



Wall::Wall() : Inanimate() {
	id = ID_WALL;
	height = WALL_HEIGHT;

	main_color = COLOR_WALL;
	second_color = COLOR_TRANSPARENT;
	base_color = COLOR_WALL_BASE;
	top_color = COLOR_WALL_TOP;
}


void Wall::drawAtPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate win_size, Coordinate pos) {
	Coordinate win_end = Coordinate(win_start, win_size);
	Coordinate i = Coordinate(pos, win_start, win_end);
	pos.setBounds(win_start, Coordinate(win_start, win_size));
	while(i.y - pos.y < height && i.y < win_end.y) {
		if(i.y == pos.y + height - 1) {
			Inanimate::drawCell(scr, i, top_color);
		}
		else if(i.y < pos.y + height) {
			if(scr[i.rel_int_y()][i.rel_int_x()].getCh() == CHAR_EMPTY || scr[i.rel_int_y()][i.rel_int_x()].getBg() == main_color) drawCell(scr, i, main_color);
			else drawCell(scr, i, second_color);
		}
		i.y++;
	}
}

