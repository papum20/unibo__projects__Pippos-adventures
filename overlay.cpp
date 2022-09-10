#include "overlay.hpp"



Overlay::Overlay() {
	
}
Overlay::Overlay(int x, int y, int width, int height) {
	this->width = width;
	this->height = height;
	window = newwin(height, width, y, x);
}

void Overlay::destroy() {
	delwin(window);
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