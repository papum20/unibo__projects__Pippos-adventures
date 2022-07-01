#include "cell.hpp"



Cell::Cell() {
	Cell(CELL_DFLT_CHAR, CELL_DFLT_FG, CELL_DFLT_BG, CELL_DFLT_ATTR);
}
Cell::Cell(char ch, int fg, int bg, attr_t att) {
	if(ch < 0) ch = CELL_DFLT_CHAR;
	if(fg < 0) fg = CELL_DFLT_FG;
	if(bg < 0) bg = CELL_DFLT_BG;
	if(att < 0) att = CELL_DFLT_ATTR;
	edit(ch, fg, bg, att);
}

void Cell::edit(char ch, int fg, int bg, attr_t att) {
	if(ch >= 0) this->ch = ch;
	if(fg >= 0)	this->fg = fg;
	if(bg >= 0) this->bg = bg;
	if(att >= 0) this->att = att;
}
chtype Cell::toChtype() {
	return ch | colorPair() | att;
}

int Cell::colorPairNumber() {
	return (COLOR_WHITE - fg) * COLORS_TOT + bg;
}
int Cell::colorPair() {
	return COLOR_PAIR(colorPairNumber());
}