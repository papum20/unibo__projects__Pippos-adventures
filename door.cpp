#include "door.hpp"



Door::Door(int x, int y, pRoom room) {
	xPos = x;
	yPos = y;
	this->room = room;
};



//// GET
void Door::getPosition(int &x, int &y) {
	x = xPos;
	y = yPos;
}
pRoom Door::getConnected() {
	return room;
}