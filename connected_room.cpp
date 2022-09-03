#include "connected_room.hpp"


#pragma region MAIN
	ConnectedRoom::ConnectedRoom(Coordinate pos) : Room(pos) {
		n_doors_max = MAX_CONNECTED_R;
		//inizializza porte/stanze collegate
		for(int i = 0; i < n_doors_max; i++) {
			connected[i] = NULL;
			map->doors[i] = NULL;
		}
		door_positions[0] = Coordinate(size.x / 2, 0);
		door_positions[1] = Coordinate(0, size.y / 2);
		door_positions[2] = Coordinate(size.x / 2, size.y - 1);
		door_positions[3] = Coordinate(size.x - 1, size.y / 2);
		locked_doors = 0;
	}
	void ConnectedRoom::recursiveDestroy() {
		for(int i = 0; i < MAX_CONNECTED_R; i++) {
			if(connected[i] != NULL) {
				//if(i < DIR_TOT) doors[i]->getConnected()->makeConnection(NULL, (i + 2) % DIR_TOT, LOCK_NONE);
				//else connected[i]->makeConnection(NULL, i, LOCK_NONE);		//scollega la stanza adiacente da questa
				connected[i]->makeConnection(NULL, i, LOCK_NONE);		//scollega la stanza adiacente da questa
				connected[i]->recursiveDestroy();						//distruggi in ricorsione la stanza adiacente
			}
		}
		Room::recursiveDestroy();										//distruggi tutto il resto della stanza
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
	Coordinate ConnectedRoom::calcDoorEntrance(Coordinate door_pos) {
		Coordinate res;
		int d = 0;
		while(d < DIRECTIONS_N) {
			if(Coordinate(door_pos, DIRECTIONS[d]).inBounds(Coordinate(0, 0), size))
				res = Coordinate(door_pos, DIRECTIONS[d].negative());
			else d++;
		}
		return res;
	}
	void ConnectedRoom::generateDoors(pUnionFind sets) {
		for(int door = 0; door < n_doors_sides; door++) {
			Coordinate door_pos = map->doors[door]->getPosition();
			door_pos.setMatrix(size);
			map->physical[door_pos.single()] = map->doors[door];
			sets->makeSet(door_pos.single());
		}
	}
#pragma endregion AUSILIARIE



#pragma region SET_GET
	void ConnectedRoom::makeConnection(pRoom room, int dir, lock_type lt, bool first) {
		if(connected[dir] == NULL && room != NULL) {
			connected[dir] = room;
			if(first) {
				if(locked_doors < LOCKED_DOORS_MAX && (lt == LOCK_OWN || lt == LOCK_BOTH)) {
					addDoor(dir, true);
					locked_doors++;
				}
				else addDoor(dir, false);
				Room::makeConnection(room, dir, lt, false);
			} else {
				if(locked_doors < LOCKED_DOORS_MAX && (lt == LOCK_OTHER || lt == LOCK_BOTH)) {
					addDoor(dir, true);
					locked_doors++;
				}
				else addDoor(dir, false);
			}
		}
	}
	void ConnectedRoom::addDoor(int dir, lock_type lt) {
		if(map->doors[dir] == NULL) map->doors[dir] = new Door(door_positions[dir], calcDoorEntrance(door_positions[dir]), lt);
	}
	bool ConnectedRoom::addLockedDoor() {
		if(locked_doors < LOCKED_DOORS_MAX) {
			locked_doors++;
			return true;
		} else return false;
	}
//// GET
	pRoom ConnectedRoom::getRoomInPosition(Coordinate pos) {
		if(!pos.inBounds(Coordinate(0, 0), size)) return NULL;
		else {
			pRoom res = NULL;
			for(int i = 0; i < MAX_CONNECTED_R; i++) {
				if(connected[i] != NULL && map->doors[i]->getPosition().equals(pos)) res = connected[i];
			}
			return res;
		}
	}
	int ConnectedRoom::getLockedDoors() {
		return locked_doors;
	}
	/*pDoor Map::getDoorInPosition(Coordinate pos) {
		bool found = false;
		int d = 0;
		while(!found && d < MAX_CONNECTED_R) {
			if(doors[d]->getPosition().equals(pos)) found = true;
			else d++;
		}
		if(!found) return NULL;
		else return doors[d];
	}*/
#pragma endregion SET_GET