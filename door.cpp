#include "door.hpp"



Door::Door(Coordinate pos, pRoom room) {
	id = ID_DOOR;
	this->pos = pos;
	this->room = room;
};

/*void Door::update() {
	if(!player_on) useable = true;
}*/

//// SET
void Door::unconnect() {
	room = NULL;
}
//// GET
pRoom Door::getConnected() {
	return room;
}


/*Door::Door(Coordinate pos) {
	id = ID_DOOR;
	this->pos = pos;
	useable = true;
	player_on = false;
};



//// BOOL
bool Door::canUse() {
	return useable;
}*/

//// SET / GET
/*void Door::setPlayerOn(bool p) {
	player_on = p;
}*/