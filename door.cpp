#include "door.hpp"



Door::Door(Coordinate pos) {
	id = ID_DOOR;
	this->pos = pos;
	useable = true;
	player_on = false;
};

void Door::update() {
	if(!player_on) useable = true;
}


//// BOOL
bool Door::canUse() {
	return useable;
}

//// SET / GET
/*void Door::setPlayerOn(bool p) {
	player_on = p;
}*/