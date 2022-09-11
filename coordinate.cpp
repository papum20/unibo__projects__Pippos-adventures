#include "coordinate.hpp"



//// COSTRUTTORI
#pragma region COSTRUTTORI
	Coordinate::Coordinate() {
		x = DFLT_COORDINATE_X;
		y = DFLT_COORDINATE_Y;
		sizex = -1, sizey = -1;
		startx = -1, starty = -1;
		endx = -1, endy = -1;
	}
	Coordinate::Coordinate(float x, float y) {
		this->x = x;
		this->y = y;
		sizex = -1, sizey = -1;
		startx = -1, starty = -1;
		endx = -1, endy = -1;
	}
	Coordinate::Coordinate(float x, float y, Coordinate size) {
		this->x = x;
		this->y = y;
		startx = -1, starty = -1;
		endx = -1, endy = -1;
		setMatrix(size);
		setBounds(Coordinate(0, 0), size);
	}
	Coordinate::Coordinate(Coordinate pos, Coordinate start, Coordinate end) {
		x = pos.x;
		y = pos.y;
		setMatrix(end);
		setBounds(start, end);
	}
	Coordinate::Coordinate(Coordinate pos, Coordinate size, Coordinate start, Coordinate end) {
		x = pos.x;
		y = pos.y;
		setMatrix(size);
		setBounds(start, end);
	}
	Coordinate::Coordinate(s_coord xy, Coordinate size) {
		setMatrix(size);
		y = (int)(xy / sizex);
		x = xy - y * sizex;
		setBounds(Coordinate(0, 0), size);
	}
	Coordinate::Coordinate(const Coordinate a, const Coordinate b) {
		x = a.x + b.x;
		y = a.y + b.y;
		setMatrix(a.size());
		setBounds(a.start(), a.end());
	}
#pragma endregion COSTRUTTORI

	Coordinate Coordinate::unitVector(Coordinate A, Coordinate B) {
		Coordinate diff = Coordinate(B, A.negative());
		int diffMax = Math::abs(diff.x);
		if(Math::abs(diff.y) > diffMax) diffMax = Math::abs(diff.y);
		if(diffMax == 0) return COORDINATE_ZERO;
		else return diff.times(1. / diffMax, 1. / diffMax);
	}


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
	bool Coordinate::equals(Coordinate B) const {
		return x == B.x && y == B.y;
	}
	bool Coordinate::equals_int(Coordinate B) const {
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
	Coordinate Coordinate::swapped() const {
		return Coordinate(Coordinate(y, x), size(), start(), end());
	}
	Coordinate Coordinate::negative() const {
		return Coordinate(Coordinate(-x, -y), size(), start(), end());
	}
	Coordinate Coordinate::times(float px, float py) const {
		return Coordinate(Coordinate(x * px, y * py), size(), start(), end());
	}
	Coordinate Coordinate::times(Coordinate B) const {
		return Coordinate(Coordinate(x * B.x, y * B.y), size(), start(), end());
	}
	Coordinate Coordinate::integer() const {
		return Coordinate(Coordinate(intx(), inty()), size(), start(), end());
	}
	Coordinate Coordinate::floor() {
		return Coordinate(Coordinate(Math::floor(x), Math::floor(y)), size(), start(), end());
	}
	Coordinate Coordinate::ceil() {
		return Coordinate(Coordinate(Math::ceil(x), Math::ceil(y)), size(), start(), end());
	}
	void Coordinate::clamp(Coordinate mn, Coordinate mx) {
		if(mn.lessEqual(mx)) {
			if(x < mn.x) x = mn.x;
			else if(x > mx.x) x = mx.x;
			if(y < mn.y) y = mn.y;
			else if(y > mx.y) y = mx.y;
		}
	}
	void Coordinate::next() {
		if(sizex >= 0 && sizey >= 0 && inBounds(Coordinate(0, 0), size())) {
			x = intx(), y = inty();
			if(x >= endx - 1 || x >= sizex - 1) {
				x = startx;
				if(y >= endy - 1 || y >= sizey - 1) y = starty;
				else y++;
			}
			else
				x++;
		}
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
		sizex = size.x, sizey = size.y;
	}
	void Coordinate::setBounds(Coordinate start, Coordinate end) {
		if(start.lessEqual(end)) {
			if(sizex < 0 || sizey < 0) sizex = end.x, sizey = end.y;
			startx = start.x;
			starty = start.y;
			endx = end.x;
			endy = end.y;
		}
	}

//GET
	Coordinate Coordinate::size() const {
		return Coordinate(sizex, sizey);
	}
	Coordinate Coordinate::start() const {
		return Coordinate(startx, starty);
	}
	Coordinate Coordinate::end() const {
		return Coordinate(endx, endy);
	}
	int Coordinate::intx() const {
		return x;
	}
	int Coordinate::inty() const {
		return y;
	}
	int Coordinate::ceilx() {
		return Math::ceil(x);
	}
	int Coordinate::ceily() {
		return Math::ceil(y);
	}
	Coordinate Coordinate::relative() {
		return Coordinate(x - startx, y - starty);
	}
	int Coordinate::rel_int_x() {
		return (int)(x - startx);
	}
	int Coordinate::rel_int_y() {
		return (int)(y - starty);
	}
	s_coord Coordinate::single() {
		if(sizex < 0 || sizey < 0 || !inBounds(Coordinate(0, 0), size())) return ERROR_INT;
		else return inty() * sizex + intx();
	}
	s_coord Coordinate::single_set(Coordinate size) {
		if(size.x < 0 || size.y < 0 || !inBounds(Coordinate(0, 0), size)) return ERROR_INT;
		else return inty() * size.x + intx();
	}
	s_coord Coordinate::single_ceil() {
		if(sizex < 0 || sizey < 0) return ERROR_INT;
		return ceily() * sizex + ceilx();
	}
#pragma endregion SET_GET