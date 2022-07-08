#include "door.hpp"



Door::Door(int x, int y, pRoom room) {
	pos = Coordinate(x, y);
	id = ID_DOOR;
	this->room = room;
};



//// GET
pRoom Door::getConnected() {
	return room;
}