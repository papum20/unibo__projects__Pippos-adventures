#include "coordinate.hpp"



//// COSTRUTTORI
#pragma region COSTRUTTORI
	Coordinate::Coordinate() {
		x = DFLT_COORDINATE_X;
		y = DFLT_COORDINATE_Y;
		setMatrix(DFLT_COORDINATE_W, DFLT_COORDINATE_H);
	}
	Coordinate::Coordinate(int x, int y) {
		this->x = x;
		this->y = y;
	}
	Coordinate::Coordinate(int x, int y, int width, int height) {
		Coordinate(x, y);
		setMatrix(width, height);
	}
	Coordinate::Coordinate(int x, int y, int sx, int sy, int ex, int ey) {
		Coordinate(x, y);
		setFullMatrix(sx, sy, ex, ey);
	}
	Coordinate::Coordinate(s_coord xy, int width, int height) {
		setMatrix(width, height);
		y = xy / width;
		x = xy - y * width;
	}
	Coordinate::Coordinate(const Coordinate a, const Coordinate b) {
		Coordinate(a.x + b.x, a.y + b.y, a.startx, a.starty, a.endx, a.endy);
	}
#pragma endregion COSTRUTTORI



//// BOOL
#pragma region BOOL
	bool Coordinate::inBounds(Coordinate mn, Coordinate mx) {
		return (x >= mn.x && x < mx.x && y >= mn.y && y < mx.y);
	}
	bool Coordinate::inOwnBounds() {
		return (x >= startx && x < endx && y >= starty && y < endy);
	}
	#pragma endregion BOOL

//// EDIT
#pragma region EDIT
	Coordinate Coordinate::times(int px, int py) {
		x *= px;
		y *= py;
		return *this;
	}
	Coordinate Coordinate::getTimes(int px, int py) {
		return Coordinate(x * px, y * py, startx, starty, endx, endy);
	}
	void Coordinate::next() {
		if(x >= endx - 1) {
			x = startx;
			if(y >= endy - 1) y = starty;
			else y++;
		}
		else
			x++;
	}
	void Coordinate::randomize(int xmin, int xmax, int ymin, int ymax) {
		if(xmin != xmax) x = rand() % (xmax - xmin) + xmin;
		if(ymin != ymax) y = rand() % (ymax - ymin) + ymin;
	}
#pragma endregion EDIT

//// SET GET
#pragma region SET_GET
// SET
	void Coordinate::setMatrix(int width, int height) {
		this->endx = width;
		this->endy = height;
	}
	void Coordinate::setFullMatrix(int sx, int ex, int sy, int ey) {
		this->startx = startx;
		this->endx = endx;
		this->starty = starty;
		this->endy = endy;
	}

//GET
	int Coordinate::relative_x() {
		return x - startx;
	}
	int Coordinate::relative_y() {
		return y - starty;
	}
	s_coord Coordinate::single() {
		return y * (endx - startx) + x;
	}
#pragma endregion SET_GET