#include "connected_room.hpp"


#pragma region MAIN
	ConnectedRoom::ConnectedRoom(Coordinate pos) : Room(pos) {
		n_doors_max = MAX_CONNECTED_R;
		//inizializza porte/stanze collegate
		for(int i = 0; i < n_doors_max; i++) {
			connected[i] = NULL;
			map->doors[i] = NULL;
		}
		door_positions[DIRECTION_UP]	= Coordinate((size.x - DOOR_WIDTH) / 2, size.y - DOOR_DEPTH);
		door_positions[DIRECTION_RIGHT]	= Coordinate(size.x - DOOR_DEPTH, (size.y - DOOR_WIDTH) / 2);
		door_positions[DIRECTION_DOWN]	= Coordinate((size.x + DOOR_WIDTH) / 2, 0);
		door_positions[DIRECTION_LEFT]	= Coordinate(0, (size.y - DOOR_WIDTH) / 2);

		door_entrances[DIRECTION_UP]	= Coordinate((size.x - p_width) / 2, size.y - DOOR_DEPTH - p_depth);
		door_entrances[DIRECTION_RIGHT]	= Coordinate(size.x - DOOR_DEPTH - p_width, (size.y - DOOR_WIDTH - p_depth) / 2);
		door_entrances[DIRECTION_DOWN]	= Coordinate((size.x - p_width) / 2, DOOR_DEPTH);
		door_entrances[DIRECTION_LEFT]	= Coordinate(DOOR_DEPTH, (size.y - DOOR_WIDTH - p_depth) / 2);

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
		////GENERA SPAZI VUOTI DAVANTI ALLE PORTE, COSÌ CHE CI RIMANGA SPAZIO
		generateDoorsPlacehodlers(sets);
		////CREA STANZA NELLA STANZA (QUADRATO VUOTO AL CENTRO)
		generateInnerRoom(sets);
		////RIEMPI LA STANZA DI MURI E CORRIDOI
		generateAllPaths(sets);
		////FAI IN MODO CHE OGNI PUNTO SIA RAGGIUNGIBILE DA OGNI ALTRO PUNTO
		connectPaths(sets);
		////RIDIMENSIONA LA STANZA, OVVERO ESEGUI UN ALLARGAMENTO DI "X_SCALE" VOLTE
		resizeMap();
		////GENERA PORTE
		generateDoors();
		//delete della struttura
		sets->destroy();
	}
#pragma endregion MAIN



#pragma region AUSILIARIE
	void ConnectedRoom::generateDoorsPlacehodlers(pUnionFind sets) {
		for(int dir = 0; dir < DIRECTIONS_N; dir++) {
			pDoor door = map->doors[dir];
			if(door != NULL) {
				Coordinate start, end;
				Coordinate door_pos_t = door->getPosition().times(1/scale.x, 1/scale.y), door_size_t = door->getSize().times(1/scale.x, 1/scale.y).ceil();
				Coordinate zone_lr_t = ZONE_DOOR_LR.times(1/scale.x, 1/scale.y).ceil(), zone_ud_t = ZONE_DOOR_UD.times(1/scale.x, 1/scale.y).ceil();
				if(dir == DIRECTION_LEFT || dir == DIRECTION_RIGHT) {
					if		(dir == DIRECTION_LEFT)	 	start = Coordinate(door_pos_t, Coordinate(door_size_t.x,(-zone_lr_t.y +door_size_t.y) / 2));
					else if (dir == DIRECTION_RIGHT)	start = Coordinate(door_pos_t, Coordinate(-zone_lr_t.x, (-zone_lr_t.y +door_size_t.y) / 2));
					end = Coordinate(start, zone_lr_t.ceil());
				} else {
					if (dir == DIRECTION_UP)	start = Coordinate(door_pos_t, Coordinate((door_size_t.x - zone_ud_t.x) / 2, -zone_ud_t.y));
					else						start = Coordinate(door_pos_t, Coordinate((-door_size_t.x - zone_ud_t.x) / 2, door_size_t.y));
					end = Coordinate(start, zone_ud_t);
				}
				Coordinate i = Coordinate(start, size, start, end);
				do {
					map->physical[i.single()] = FLOOR_INSTANCE;
					sets->makeSet(i.single());
					i.next();
				} while(!i.equals(start));
			}
		}
	}
	void ConnectedRoom::generateDoors() {
		for(int door = 0; door < n_doors_max; door++) {
			if(map->doors[door] != NULL) {
				Coordinate door_pos = map->doors[door]->getPosition();
				Coordinate i = Coordinate(door_pos, size, door_pos, Coordinate(door_pos, map->doors[door]->getSize()));
				do {
					map->physical[i.single()] = map->doors[door];
					i.next();
				} while(!i.equals(door_pos));
			}
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
		Coordinate door_size = DOOR_SIZE;
		if(dir == DIRECTION_LEFT || dir == DIRECTION_RIGHT) door_size = door_size.swapped();
		if(map->doors[dir] == NULL) map->doors[dir] = new Door(door_positions[dir], door_size, door_entrances[dir], lt);
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