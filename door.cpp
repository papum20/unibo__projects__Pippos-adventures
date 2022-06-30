#include "door.hpp"



Door::Door(int x, int y, pRoom room) {
	xPos = x;
	yPos = y;
	this->room = room;
};



//// GET
pRoom Door::getConnected() {
	return room;
}