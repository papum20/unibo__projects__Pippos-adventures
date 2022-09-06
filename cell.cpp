#include "cell.hpp"



Cell::Cell() {
	edit(CELL_DFLT_CHAR, CELL_DFLT_FG, CELL_DFLT_BG, CELL_DFLT_ATTR);
}
Cell::Cell(char ch, int fg, int bg, attr_t att) {
	if(ch < 0) ch = CELL_DFLT_CHAR;
	if(fg < 0) fg = CELL_DFLT_FG;
	if(bg < 0) bg = CELL_DFLT_BG;
	if(att == CELL_NO_ATTR) att = CELL_DFLT_ATTR;
	edit(ch, fg, bg, att);
}

void Cell::initPairs() {
	for(int fg = 0; fg < COLORS_NUMBER; fg++)
		for(int bg = 0; bg < COLORS_NUMBER; bg++) init_pair(pairNumber(fg, bg), fg, bg);
}

void Cell::edit(char ch, int fg, int bg, attr_t att) {
	if(ch >= 0) this->ch = ch;
	if(fg >= 0)	this->fg = fg;
	if(bg >= 0) this->bg = bg;
	if(att != CELL_NO_ATTR) this->att = att;
}

/// GET
char Cell::getCh() {
	return ch;
}
int Cell::getBg() {
	return bg;
}
chtype Cell::toChtype() {
	return ch | colorPair() | att;
}

int Cell::pairNumber(int fg, int bg) {
	return fg * COLORS_NUMBER + bg + 1;
}
int Cell::pairNumber_own() {
	return pairNumber(fg, bg);
}
int Cell::colorPair() {
	return COLOR_PAIR(pairNumber_own());
}