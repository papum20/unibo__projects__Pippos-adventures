#include "door.hpp"



	Door::Door(Coordinate pos, pRoom room, Coordinate entrancePosition) {
		id = ID_DOOR;
		this->pos = pos;
		this->room = room;
		this->entrancePosition = entrancePosition;
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
	Coordinate Door::getEntrancePosition() {
		return entrancePosition;
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