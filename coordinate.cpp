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
		this->x = x;
		this->y = y;
		setMatrix(size);
	}
	Coordinate::Coordinate(Coordinate pos, Coordinate start, Coordinate end) {
		x = pos.x;
		y = pos.y;
		setFullMatrix(start, end);
	}
	Coordinate::Coordinate(s_coord xy, Coordinate size) {
		setMatrix(size);
		y = (int)(xy / size.x);
		x = xy - y * size.x;
	}
	Coordinate::Coordinate(const Coordinate a, const Coordinate b) {
		x = a.x + b.x;
		y = a.y + b.y;
		setFullMatrix(Coordinate(a.startx, a.starty), Coordinate(a.endx, a.endy));
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
	bool Coordinate::equals_int(Coordinate B) {
		return intx() == B.intx() && inty() == B.inty();
	}
	bool Coordinate::lessEqual(Coordinate B) {
		return x <= B.x && y <= B.y;
	}
	//bool Coordinate::equalsDirection(Coordinate B) {
	//	float proportion_b_y = B.x * y / x;
	//	return proportion_b_y == B.y;
	//}
	#pragma endregion BOOL

//// EDIT
#pragma region EDIT
	Coordinate Coordinate::negative() const {
		return Coordinate(Coordinate(-x, -y), Coordinate(startx, starty), Coordinate(endx, endy));
	}
	Coordinate Coordinate::times(float px, float py) {
		return Coordinate(Coordinate(x * px, y * py), Coordinate(startx, starty), Coordinate(endx, endy));
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
	void Coordinate::setFullMatrix(Coordinate start, Coordinate end) {
		if(start.x <= 0) start.x = startx;
		if(end.x <= 0) end.x = endx;
		if(start.y <= 0) start.y = starty;
		if(end.y <= 0) end.y = endy;
		if(start.x < end.x) {
			startx = start.x;
			endx = end.x;
		} else {
			startx = end.x;
			endx = start.x;
		}
		if(start.y < end.y) {
			starty = start.y;
			endy = end.y;
		} else {
			starty = end.y;
			endy = start.y;
		}
	}

//GET
	int Coordinate::intx() {
		return x;
	}
	int Coordinate::inty() {
		return y;
	}
	int Coordinate::ceilx() {
		return Math::ceil(x);
	}
	int Coordinate::ceily() {
		return Math::ceil(y);
	}
	float Coordinate::relative_x() {
		return x - startx;
	}
	float Coordinate::relative_y() {
		return y - starty;
	}
	s_coord Coordinate::single() {
		return inty() * (endx - startx) + intx();
	}
	s_coord Coordinate::single_ceil() {
		return ceily() * (endx - startx) + ceilx();
	}
#pragma endregion SET_GET