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
		door_positions[DIRECTION_DOWN]	= Coordinate((size.x - DOOR_WIDTH) / 2, 0);
		door_positions[DIRECTION_LEFT]	= Coordinate(0, (size.y - DOOR_WIDTH) / 2);

		door_entrances[DIRECTION_UP]	= Coordinate((size.x - p_width) / 2, size.y - DOOR_DEPTH - p_depth);
		door_entrances[DIRECTION_RIGHT]	= Coordinate(size.x - DOOR_DEPTH - p_width, (size.y - p_depth) / 2);
		door_entrances[DIRECTION_DOWN]	= Coordinate((size.x - p_width) / 2, DOOR_DEPTH);
		door_entrances[DIRECTION_LEFT]	= Coordinate(DOOR_DEPTH, (size.y - p_depth) / 2);

		door_zones_t[DIRECTION_UP]		= Coordinate((size_t.x - ZONE_DOOR_UD.x/scale.x) / 2, size_t.y - 1 - ZONE_DOOR_UD.y/scale.y);
		door_zones_t[DIRECTION_RIGHT]	= Coordinate(size_t.x - 1 - ZONE_DOOR_LR.x/scale.x, (size_t.y - ZONE_DOOR_LR.y/scale.y) / 2);
		door_zones_t[DIRECTION_DOWN] 	= Coordinate((size_t.x - ZONE_DOOR_UD.x/scale.x) / 2, 1);
		door_zones_t[DIRECTION_LEFT] 	= Coordinate(1, (size_t.y - ZONE_DOOR_LR.y/scale.y) / 2);

		locked_doors = 0;
		destroyed = false;
	}
	void ConnectedRoom::recursiveDestroy() {
		destroyed = true;
		for(int dir = 0; dir < MAX_CONNECTED_R; dir++) {
			if(connected[dir] != NULL && !connected[dir]->wasDestroyed())
				connected[dir]->recursiveDestroy();						//distruggi in ricorsione la stanza adiacente
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
				Coordinate end = Coordinate(door_zones_t[dir], ZONE_DOOR_LR.times(1 / scale.x, 1 / scale.y).ceil());
				if(dir == DIRECTION_UP || dir == DIRECTION_DOWN) end = Coordinate(door_zones_t[dir], ZONE_DOOR_UD.times(1 / scale.x, 1 / scale.y).ceil());
				Coordinate i = Coordinate(door_zones_t[dir], size, door_zones_t[dir], end);
				do {
					map->physical[i.single()] = FLOOR_INSTANCE;
					sets->makeSet(i.single());
					i.next();
				} while(!i.equals(door_zones_t[dir]));
			}
		}
	}
	void ConnectedRoom::generateDoors() {
		for(int dir = 0; dir < n_doors_max; dir++) {
			if(map->doors[dir] != NULL) {
				Coordinate door_pos = map->doors[dir]->getPosition(), door_size = map->doors[dir]->getSize();
				Coordinate i = Coordinate(door_pos.integer(), size, door_pos.integer(), Coordinate(door_pos, door_size).integer());
				//posiziona porte
				do {
					map->physical[i.single()] = map->doors[dir];
					i.next();
				} while(!i.equals_int(door_pos));
				//posiziona spazio vuoto davanti (al posto dei muri)
				Coordinate start, end, mx = scale;
				if((dir == DIRECTION_UP || dir == DIRECTION_DOWN) && door_size.y > scale.y) mx.y = door_size.y;
				else if(door_size.x > scale.x) mx.x = door_size.x;
				if(dir == DIRECTION_UP) {
					start	= Coordinate(door_pos.x, size.y - mx.y);
					end		= Coordinate(door_pos.x + door_size.x, door_pos.y);
				} else if(dir == DIRECTION_RIGHT) {
					start	= Coordinate(size.x - mx.x, door_pos.y);
					end		= Coordinate(door_pos.x, door_pos.y + door_size.y);
				} else if(dir == DIRECTION_DOWN) {
					start	= Coordinate(door_pos.x, door_pos.y + 1);
					end		= Coordinate(door_pos.x + door_size.x, mx.y);
				} else {
					start	= Coordinate(door_size.x, door_pos.y);
					end		= Coordinate(mx.x, door_pos.y + door_size.y);
				}
					//WINDOW *w = newwin(10,10, 10,0);
					//mvwprintw(w,1,1,to_string(start.x).c_str());
					//mvwprintw(w,2,1,to_string(start.y).c_str());
					//mvwprintw(w,3,1,to_string(end.x).c_str());
					//mvwprintw(w,4,1,to_string(end.y).c_str());
					//mvwprintw(w,5,1,to_string(mx.x).c_str());
					//mvwprintw(w,6,1,to_string(mx.y).c_str());
					//wgetch(w);
				i = Coordinate(start.integer(), size, start.integer(), end.integer());
				do {
					map->physical[i.single()] = FLOOR_INSTANCE;
					i.next();
				} while(!i.equals_int(start));
			}
		}
	}

	int ConnectedRoom::keyChestsNumber() {
		return locked_doors;
	}
#pragma endregion AUSILIARIE



#pragma region SET_GET
	void ConnectedRoom::addDoor(int dir, lock_type lt, bool boss) {
		Coordinate door_size = DOOR_SIZE;
		if(dir == DIRECTION_LEFT || dir == DIRECTION_RIGHT) door_size = door_size.swapped();
		if(map->doors[dir] == NULL) map->doors[dir] = new Door(door_positions[dir], door_size, door_entrances[dir], lt, boss);
	}
	bool ConnectedRoom::addLockedDoor() {
		if(locked_doors < LOCKED_DOORS_MAX) {
			locked_doors++;
			return true;
		} else return false;
	}
	void ConnectedRoom::makeConnection(pRoom room, int dir, lock_type lt, bool first) {
		if(connected[dir] == NULL && room != NULL) {
			connected[dir] = room;
			if(first) {
				if(locked_doors < LOCKED_DOORS_MAX && (lt == LOCK_OWN || lt == LOCK_BOTH)) {
					addDoor(dir, true);
					locked_doors++;
				}
				else addDoor(dir, false);
				Room::makeConnection(room, dir, lt, true);
			} else {
				if(locked_doors < LOCKED_DOORS_MAX && (lt == LOCK_OTHER || lt == LOCK_BOTH)) {
					addDoor(dir, true);
					locked_doors++;
				}
				else addDoor(dir, false);
			}
		}
	}
	void ConnectedRoom::unlockDoor(pDoor door) {
		//PARTE COMMENTATA: per sbloccare anche dall'altro lato
		//pRoom adjacent = NULL;
		//int dir = 0;
		//while(adjacent == NULL && dir < DIRECTIONS_N) {
		//	if(map->doors[dir] == door) adjacent = connected[dir];
		//	else dir++;
		//}
		door->unlock();
		//adjacent->getDoor((dir + 2) % DIRECTIONS_N)->unlock();
	}
//// GET
	pRoom ConnectedRoom::getConnectedRoom(pDoor door) {
		int dir = doorDirection(door);
		if(dir != DIRECION_ERROR) return connected[dir];
		else return NULL;
	}
	Coordinate ConnectedRoom::getEntrance(pDoor door) {
		int dir = doorDirection(door);
		if(dir == DIRECION_ERROR) return COORDINATE_ERROR;
		else return connected[dir]->getDoor((dir + 2) % DIRECTIONS_N)->getEntrancePosition();
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


#pragma region SPAWN

	void ConnectedRoom::spawn(int level, pCharacter player, bool current) {
		int key_chests = keyChestsNumber();
		for(int i = 0; i < key_chests; i++) spawnChest(new Chest(new Key()));
		Room::spawn(level, player, current);
	}

#pragma endregion