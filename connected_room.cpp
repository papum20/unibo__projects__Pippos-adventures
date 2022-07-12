#include "connected_room.hpp"


#pragma region MAIN
	ConnectedRoom::ConnectedRoom(Coordinate pos) : Room(pos) {
		//inizializza porte/stanze collegate
		n_doors_max = MAX_CONNECTED_R;
		for(int i = 0; i < n_doors_max; i++) doors[i] = NULL;

		door_positions[0] = Coordinate(size.x / 2, 0);
		door_positions[1] = Coordinate(0, size.y / 2);
		door_positions[2] = Coordinate(size.x / 2, size.y - 1);
		door_positions[3] = Coordinate(size.x - 1, size.y / 2);
	}
	void ConnectedRoom::recursiveDestroy() {
		for(int i = 0; i < MAX_CONNECTED_R; i++) {
			if(doors[i] != NULL && doors[i]->getConnected() != NULL) {
				if(i < DIR_TOT) doors[i]->getConnected()->makeConnection(NULL, (i + 2) % DIR_TOT);
				else doors[i]->getConnected()->makeConnection(NULL, i);					//scollega la stanza adiacente da questa
				doors[i]->getConnected()->recursiveDestroy();							//distruggi in ricorsione la stanza adiacente
				doors[i]->destroy();													//distruggi la porta
			}
		}
		Room::recursiveDestroy();														//distruggi tutto il resto della stanza
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
			door_p.setMatrix(size);
			grid[door_p.inty()][door_p.intx()] = doors[door];
			sets->makeSet(door_p.single());
		}
	}
	pDoor ConnectedRoom::findDoor(Coordinate pos) {
		if(!pos.inBounds(Coordinate(0, 0), size)) return NULL;
		else {
			pDoor res = NULL;
			for(int i = 0; i < MAX_CONNECTED_R; i++) {
				if(doors[i] != NULL && doors[i]->getPosition().equals(pos)) res = doors[i];
			}
			return res;
		}
	}
#pragma endregion AUSILIARIE

#pragma region SET_GET
//// SET
	void ConnectedRoom::makeConnection(pConnectedRoom room, int dir) {
		this->doors[dir] = new Door(door_positions[dir], room);
		int dir2 = (dir + 2) % DIR_TOT;
		room->doors[dir2] = new Door(door_positions[dir2], this);
	}
//// GET
	pRoom ConnectedRoom::getConnectedRoom(Coordinate pos) {
			return findDoor(pos)->getConnected();
	}
	pRoom ConnectedRoom::getRoomInDirection(int dir) {
		if(dir < 0 || dir >= MAX_SIDES_R || doors[dir] == NULL) return NULL;
		else return doors[dir]->getConnected();
	}
/*	int Room::getSideDoors() {
		return n_doors_sides;
	}*/
#pragma endregion SET_GET