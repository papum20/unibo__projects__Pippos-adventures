#include "door.hpp"



Door::Door(Coordinate pos, pRoom room) {
	id = ID_DOOR;
	this->pos = pos;
	this->room = room;
};


//// SET
void Door::unconnect() {
	room = NULL;
}
//// GET
pRoom Door::getConnected() {
	return room;
}