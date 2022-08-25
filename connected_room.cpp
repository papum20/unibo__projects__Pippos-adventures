#include "connected_room.hpp"


#pragma region MAIN
	ConnectedRoom::ConnectedRoom(Coordinate pos) : Room(pos) {
		//inizializza porte/stanze collegate
		n_doors_max = MAX_CONNECTED_R;
		for(int i = 0; i < n_doors_max; i++) {
			doors[i] = NULL;
			//connected[i] = NULL;
		}

		door_positions[0] = Coordinate(size.x / 2, 0);
		door_positions[1] = Coordinate(0, size.y / 2);
		door_positions[2] = Coordinate(size.x / 2, size.y - 1);
		door_positions[3] = Coordinate(size.x - 1, size.y / 2);
	}
	void ConnectedRoom::recursiveDestroy() {
		for(int i = 0; i < MAX_CONNECTED_R; i++) {
			/*if(doors[i] != NULL && connected[i] != NULL) {
				if(i < DIR_TOT) connected[i]->makeConnection(NULL, (i + 2) % DIR_TOT);
				else connected[i]->makeConnection(NULL, i);				//scollega la stanza adiacente da questa
				connected[i]->recursiveDestroy();						//distruggi in ricorsione la stanza adiacente
				doors[i]->destroy();									//distruggi la porta
			}*/
			if(doors[i] != NULL && doors[i]->getConnected() != NULL) {
				if(i < DIR_TOT) doors[i]->getConnected()->makeConnection(NULL, (i + 2) % DIR_TOT);
				else doors[i]->getConnected()->makeConnection(NULL, i);		//scollega la stanza adiacente da questa
				doors[i]->getConnected()->recursiveDestroy();				//distruggi in ricorsione la stanza adiacente
				doors[i]->destroy();										//distruggi la porta
			}
		}
		Room::recursiveDestroy();											//distruggi tutto il resto della stanza
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

	/*void ConnectedRoom::update(char input) {
		Room::update(input);
		//imposta il player non sulla porta per ogni porta
		for(int d = 0; d < MAX_CONNECTED_R; d++) {
			if(doors[d] != NULL) {
				doors[d]->setPlayerOn(false);
				doors[d]->update();
			}
		}
	}*/
#pragma endregion MAIN

#pragma region AUSILIARIE
	void ConnectedRoom::generateDoors(pUnionFind sets) {
		for(int door = 0; door < n_doors_sides; door++) {
			Coordinate door_p = doors[door]->getPosition();
			door_p.setMatrix(size);
			map[door_p.single()] = doors[door];
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
	Coordinate ConnectedRoom::getDoorEntrance(Coordinate doorCenter) {
		Coordinate res;
		int d = 0;
		while(d < DIR_TOT) {
			if(!Coordinate(doorCenter, DIRECTIONS[d]).inBounds(Coordinate(0, 0), size))
				res = Coordinate(doorCenter, DIRECTIONS[d].getNegative());
			else d++;
		}
		return res;
	}
#pragma endregion AUSILIARIE

#pragma region SET_GET
//// SET
	/*void ConnectedRoom::makeConnection(pConnectedRoom room, int dir) {
		this->doors[dir] = new Door(door_positions[dir]);
		connected[dir] = room;
		int dir2 = (dir + 2) % DIR_TOT;
		room->doors[dir2] = new Door(door_positions[dir2]);
		room->connected[dir2] = this;
	}*/
	void ConnectedRoom::makeConnection(pRoom room, int dir) {
		if(doors[dir] == NULL) {
			doors[dir] = new Door(door_positions[dir], room, getDoorEntrance(door_positions[dir]));
			Room::makeConnection(room, dir);
		}
	}
//// GET
	/*pConnectedRoom ConnectedRoom::getRoomInPosition(Coordinate pos) {
		if(!pos.inBounds(Coordinate(0, 0), size)) return NULL;
		else {
			pConnectedRoom res = NULL;
			for(int i = 0; i < MAX_CONNECTED_R; i++) {
				if(connected[i] != NULL && doors[i]->getPosition().equals(pos)) res = connected[i];
			}
			return res;
		}
	}
	pConnectedRoom ConnectedRoom::getRoomInDirection(int dir) {
		if(dir < 0 || dir >= MAX_SIDES_R || doors[dir] == NULL) return NULL;
		else return connected[dir];
	}*/
	pRoom ConnectedRoom::getRoomInPosition(Coordinate pos) {
			return findDoor(pos)->getConnected();
	}
	pRoom ConnectedRoom::getRoomInDirection(int dir) {
		if(dir < 0 || dir >= MAX_SIDES_R || doors[dir] == NULL) return NULL;
		else return doors[dir]->getConnected();
	}
	pDoor ConnectedRoom::getDoorInPosition(Coordinate pos) {
		bool found = false;
		int d = 0;
		while(!found && d < MAX_CONNECTED_R) {
			if(doors[d]->getPosition().equals(pos)) found = true;
			else d++;
		}
		if(!found) return NULL;
		else return doors[d];
	}
	pDoor ConnectedRoom::getDoorToRoom(pConnectedRoom room) {
		if(room != NULL) {
			bool found = false;
			int d = 0;
			while(d < MAX_CONNECTED_R && found == false) {
				//if(connected[d] == room) found = true;
				if(doors[d]->getConnected() == room) found = true;
				else d++;
			}
			if(!found) return NULL;
			else return doors[d];
		}
		else return NULL;
	}
/*	int Room::getSideDoors() {
		return n_doors_sides;
	}*/
#pragma endregion SET_GET