#include "door.hpp"



Door::Door(int x, int y, pRoom room) {
	xPos = x;
	yPos = y;
	this->room = room;
};



//// GET
void Door::getConnected() {
	return room;
}