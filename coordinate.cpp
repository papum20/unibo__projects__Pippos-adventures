#include "coordinate.hpp"



//// COSTRUTTORI
#pragma region COSTRUTTORI
	Coordinate::Coordinate() {
		x = DFLT_COORDINATE_X;
		y = DFLT_COORDINATE_Y;
		setMatrix(Coordinate(DFLT_COORDINATE_W, DFLT_COORDINATE_H));
	}
	Coordinate::Coordinate(float x, float y) {
		this->x = x;
		this->y = y;
	}
	Coordinate::Coordinate(float x, float y, Coordinate size) {
		Coordinate(x, y);
		setMatrix(size);
	}
	Coordinate::Coordinate(float x, float y, float sx, float sy, float ex, float ey) {
		Coordinate(x, y);
		setFullMatrix(sx, sy, ex, ey);
	}
	Coordinate::Coordinate(s_coord xy, Coordinate size) {
		setMatrix(size);
		y = xy / size.x;
		x = xy - y * size.x;
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
	/*bool Coordinate::inBoundsX(float xmin, float xmax) {
		return (x >= xmin && x <= xmax); 
	}
	bool Coordinate::inBoundsY(float ymin, float ymax) {
		return (y >= ymin && y <= ymax);
	}*/
	bool Coordinate::equals(Coordinate B) {
		return x == B.x && y == B.y;
	}
	//bool Coordinate::equalsDirection(Coordinate B) {
	//	float proportion_b_y = B.x * y / x;
	//	return proportion_b_y == B.y;
	//}
	#pragma endregion BOOL

//// EDIT
#pragma region EDIT
	Coordinate Coordinate::negative() {
		x = -x;
		y = -y;
		return *this;
	}
	Coordinate Coordinate::getNegative() const {
		Coordinate copy = *this;
		copy.x = -x;
		copy.y = -y;
		return copy;
	}
	Coordinate Coordinate::times(float px, float py) {
		x *= px;
		y *= py;
		return *this;
	}
	Coordinate Coordinate::getTimes(float px, float py) {
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
	void Coordinate::setMatrix(Coordinate size) {
		if(size.x > 0) this->endx = startx + size.x;
		if(size.y > 0) this->endy = starty + size.y;
	}
	void Coordinate::setFullMatrix(float sx, float ex, float sy, float ey) {
		if(sx <= 0) sx = startx;
		if(ex <= 0) ex = endx;
		if(sy <= 0) sy = starty;
		if(ey <= 0) ey = endy;
		if(sx < ex) {
			startx = sx;
			endx = ex;
		}
		if(sy < ey) {
			starty = sy;
			endy = ey;
		}
	}

//GET
	int Coordinate::intx() {
		return x;
	}
	int Coordinate::inty() {
		return y;
	}
	float Coordinate::relative_x() {
		return x - startx;
	}
	float Coordinate::relative_y() {
		return y - starty;
	}
	s_coord Coordinate::single() {
		return y * (endx - startx) + x;
	}
#pragma endregion SET_GET