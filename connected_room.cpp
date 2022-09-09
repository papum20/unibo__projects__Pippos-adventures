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

		door_zones_t[DIRECTION_UP]	= Coordinate((size_t.x - Math::ceil(ZONE_DOOR_UD.x/scale.x)) / 2, size_t.y - 1 - Math::ceil(ZONE_DOOR_UD.y/scale.y)).integer();
		door_zones_t[DIRECTION_RIGHT]	= Coordinate(size_t.y - 1 - Math::ceil(ZONE_DOOR_LR.x), (size_t.y - Math::ceil(ZONE_DOOR_LR.y)) / 2).integer();
		door_zones_t[DIRECTION_DOWN] 	= Coordinate((size_t.x - Math::ceil(ZONE_DOOR_UD.x/scale.x)) / 2, 1).integer();
		door_zones_t[DIRECTION_LEFT] 	= Coordinate(1, (size_t.y - Math::ceil(ZONE_DOOR_LR.y)) / 2).integer();

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
	void ConnectedRoom::generate(bool c)
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
		generateDoors(c);
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
	void ConnectedRoom::generateDoors(bool c) {
		for(int dir = 0; dir < n_doors_max; dir++) {
			if(map->doors[dir] != NULL) {
				Coordinate door_pos = map->doors[dir]->getPosition(), door_size = map->doors[dir]->getSize();
				Coordinate i = Coordinate(door_pos, size, door_pos, Coordinate(door_pos, door_size));
				//posiziona porte
				do {
					map->physical[i.single()] = map->doors[dir];
					i.next();
				} while(!i.equals(door_pos));
				//posiziona spazio vuoto davanti (al posto dei muri)
				Coordinate start, end, mx = scale;
				if((dir == DIRECTION_UP || dir == DIRECTION_DOWN) && door_size.y > scale.y) mx.y = door_size.y;
				else if(door_size.x > scale.x) mx.x = door_size.x;
				if(dir == DIRECTION_UP) {
					start	= Coordinate(door_pos.x, size.y - mx.y);
					end		= Coordinate(door_pos.x + door_size.x, door_pos.y);
				} else if(dir == DIRECTION_RIGHT) {
					start	= Coordinate(size.x - mx.x, door_pos.y);
					end		= Coordinate(door_pos.x - 1, door_pos.y + door_size.y);
				} else if(dir == DIRECTION_DOWN) {
					start	= Coordinate(door_pos.x, door_pos.y + 1);
					end		= Coordinate(door_pos.x + door_size.x, mx.y);
				} else {
					start	= Coordinate(door_size.x, door_pos.y);
					end		= Coordinate(mx.x, door_pos.y + door_size.y);
				}
				if(c) {
					//WINDOW *w = newwin(10,10, 10,0);
					//mvwprintw(w,1,1,to_string(start.x).c_str());
					//mvwprintw(w,2,1,to_string(start.y).c_str());
					//mvwprintw(w,3,1,to_string(end.x).c_str());
					//mvwprintw(w,4,1,to_string(end.y).c_str());
					//mvwprintw(w,5,1,to_string(mx.x).c_str());
					//mvwprintw(w,6,1,to_string(mx.y).c_str());
					//wgetch(w);
				}
				i = Coordinate(start, size, start, end);
				do {
					map->physical[i.single()] = FLOOR_INSTANCE;
					i.next();
				} while(!i.equals(start));
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