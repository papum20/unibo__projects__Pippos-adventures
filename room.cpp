#include "room.hpp"



	Room::Room(short x, short y) {
		//inzializza stanza
		this->x = x;
		this->y = y;
		width = ROOM_WIDTH;
		height = ROOM_HEIGHT;
		for(int y = 0; y < height; y++)
			for(int x = 0; x < width; x++) grid[y][x] = NULL;
		//inizializza porte/stanze collegate
		n_doors_max = MAX_CONNECTED_R;
		for(int i = 0; i < n_doors_max; i++) doors[i] = NULL;
	}



//// SET
	void Room::makeConnection(pRoom room, short dir) {
		short dir2 = (dir+2) % DIR_SIZE;
		if(dir == 0) {			//su
			this->doors[dir] = new Door(this->width/2, 0, room);
			room->doors[dir2] = new Door(room->width/2, room->height-1, this);
		} else if(dir == 1) {	//destra
			this->doors[dir] = new Door(this->width-1, this->height/2, room);
			room->doors[dir2] = new Door(0, room->height/2, this);
		} else if(dir == 2) {	//giu
			this->doors[dir] = new Door(this->width/2, this->height-1, room);
			room->doors[dir2] = new Door(room->width/2, 0, this);
		} else if(dir == 3) {	//sinistra
			this->doors[dir] = new Door(0, this->height/2, room);
			room->doors[dir2] = new Door(room->width-1, room->height/2, this);
		}
	}
//// GET
	short Room::getX() {
		return x;
	}
	short Room::getY() {
		return y;
	}
	pRoom Room::getConnectedRoom(short dir) {
		if(dir < 0 || dir >= n_doors_max || doors[dir] == NULL) return NULL;
		else return doors[dir]->getConnected();
	}

	short Room::getSideDoors() {
		return n_doors_sides;
	}