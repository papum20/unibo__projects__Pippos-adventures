#include "door.hpp"


	Door::Door(Coordinate pos, Coordinate entrancePosition, bool locked) : Inanimate() {
		id = ID_DOOR;
		this->pos = pos;
		this->entrancePosition = entrancePosition;
		this->locked = locked;
	};

//// SET
	void Door::unlock() {
		locked = false;
	}
//// GET
	Coordinate Door::getEntrancePosition() {
		return entrancePosition;
	}
	bool Door::isLocked() {
		return locked;
	}
	