#include "room.hpp"



Room::Room() {
	//inzializza stanza
	width = ROOM_WIDTH;
	height = ROOM_HEIGHT;
	for(int y = 0; y < height; y++)
		for(int x = 0; x < width; x++) grid[y][x] = NULL;
	//inizializza porte/stanze collegate
	n_doors_max = MAX_CONNECTED_ROOMS;
	for(int i = 0; i < n_doors_max; i++) doors[i] = NULL;
}




//// GET
pRoom Room::getConnectedRoom(int dir) {
	if(dir < 0 || dir >= n_doors || doors[dir] == NULL) return NULL;
	else return doors[dir]->getConnected();
}

int Room::getSideDoors() {
	return n_doors_sides;
}