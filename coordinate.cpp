#include "coordinate.hpp"





Coordinate::Coordinate() {
	x = -1;
	y = -1;	
}
Coordinate::Coordinate(int x, int y) {
	this->x = x;
	this->y = y;
}
Coordinate::Coordinate(s_coord xy, int width) {
	y = xy / width;
	x = xy - y * width;
}



bool Coordinate::inBounds(Coordinate mn, Coordinate mx) {
	return (x >= mn.x && x < mx.x && y >= mn.y && y < mx.y);
}

s_coord Coordinate::single(int width) {
	return y * width + x;
}

void Coordinate::randomize(int xmin, int xmax, int ymin, int ymax) {
	if(xmin != xmax) x = rand() % (xmax - xmin) + xmin;
	if(ymin != ymax) y = rand() % (ymax - ymin) + ymin;
}
