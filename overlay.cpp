#include "overlay.hpp"



Overlay::Overlay() {
	window = NULL;
}
Overlay::Overlay(int x, int y, int width, int height) {
	this->width = width;
	this->height = height;
	window = newwin(height, width, y, x);
}

void Overlay::destroy() {
	if(window != NULL) delwin(window);
	delete this;
}

void Overlay::open() {
	box(window, 0, 0);
	wrefresh(window);
}

void Overlay::open_over(Overlay *B) {
	B->close();
	open();
}

void Overlay::close() {
	werase(window);
	wrefresh(window);
}