#include "overlay.hpp"



Overlay::Overlay() {
	
}
Overlay::Overlay(int x, int y, int width, int height) {
	this->width = width;
	this->height = height;
	window = newwin(height, width, y, x);
	is_open=false;
}

void Overlay::destroy() {
	delwin(window);
}

void Overlay::open() {
	is_open=true;
	box(window, 0, 0);
	wrefresh(window);
}

void Overlay::open_over(Overlay *B) {
	B->close();
	open();
}

void Overlay::close() {
	is_open=false;
	werase(window);
	wrefresh(window);
}