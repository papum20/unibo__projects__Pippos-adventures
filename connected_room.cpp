#include "connected_room.hpp"


#pragma region MAIN
	ConnectedRoom::ConnectedRoom(int x, int y) : Room(x, y) {
		//inizializza porte/stanze collegate
		n_doors_max = MAX_CONNECTED_R;
		for(int i = 0; i < n_doors_max; i++) doors[i] = NULL;
	}

	void ConnectedRoom::generate()
	{
		pUnionFind sets = new UnionFind();
		//GENERA MURI LATERALI
		generateSidesWalls();
		//GENERA PORTE
		generateDoors(sets);
		//CREA STANZA NELLA STANZA (QUADRATO VUOTO AL CENTRO)
		generateInnerRoom();
		//RIEMPI LA STANZA DI MURI E CORRIDOI
		generateAllPaths(sets);
		//FAI IN MODO CHE OGNI PUNTO SIA RAGGIUNGIBILE DA OGNI ALTRO PUNTO
		connectPaths(sets);
		//RIDIMENSIONA LA STANZA, OVVERO ESEGUI UN ALLARGAMENTO DI "X_SCALE" VOLTE
		resizeMap();
	}
#pragma endregion MAIN

#pragma region AUSILIARIE
	void ConnectedRoom::generateDoors(pUnionFind sets) {
		for(int door = 0; door < n_doors_sides; door++) {
			Coordinate door_p = doors[door]->getPosition();
			door_p.setMatrix(width, height);
			grid[door_p.y][door_p.x] = doors[door];
			sets->makeSet(door_p.single());
		}
	}
#pragma endregion AUSILIARIE

#pragma region SET_GET
//// SET
	void ConnectedRoom::makeConnection(pCRoom room, int dir) {
		int dir2 = (dir+2) % DIR_SIZE;
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
	pRoom ConnectedRoom::getConnectedRoom(int dir) {
		if(dir < 0 || dir >= n_doors_max || doors[dir] == NULL) return NULL;
		else return doors[dir]->getConnected();
	}
/*	int Room::getSideDoors() {
		return n_doors_sides;
	}*/
#pragma endregion SET_GET