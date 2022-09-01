#include "connected_room.hpp"


#pragma region MAIN
	ConnectedRoom::ConnectedRoom(Coordinate pos) : Room(pos) {
		for(int i = 0; i < map->get_n_doors_max(); i++) connected[i] = NULL;	//inizializza porte/stanze collegate
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
#pragma endregion MAIN


#pragma region SET_GET
	void ConnectedRoom::makeConnection(pRoom room, int dir, lock_type lt, bool first = true) {
		if(connected[dir] == NULL && room != NULL) {
			connected[dir] = room;
			if(first) {
				if(locked_doors < LOCKED_DOORS_MAX && (lt == LOCK_OWN || lt == LOCK_BOTH)) {
					map->addDoor(dir, true);
					locked_doors++;
				}
				else map->addDoor(dir, false);
				Room::makeConnection(room, dir, lt, false);
			} else {
				if(locked_doors < LOCKED_DOORS_MAX && (lt == LOCK_OTHER || lt == LOCK_BOTH)) {
					map->addDoor(dir, true);
					locked_doors++;
				}
				else map->addDoor(dir, false);
			}
		}
	}
	bool ConnectedRoom::addLockedDoor() {
		if(locked_doors < LOCKED_DOORS_MAX) {
			locked_doors++;
			return true;
		} else return false;
	}
//// GET
	pRoom ConnectedRoom::getRoomInPosition(Coordinate pos) {
		if(!pos.inBounds(Coordinate(0, 0), map->getSize())) return NULL;
		else {
			pRoom res = NULL;
			for(int i = 0; i < MAX_CONNECTED_R; i++) {
				if(connected[i] != NULL && map->getDoorInIndex(i)->getPosition().equals(pos)) res = connected[i];
			}
			return res;
		}
	}
	int ConnectedRoom::getLockedDoors() {
		return locked_doors;
	}
#pragma endregion SET_GET