#include "map.hpp"


Map::Map(int scale_x, pInanimate floorInstance, pInanimate wallInstance) {
	//variabili
	this->scale_x = scale_x;
	size = Coordinate(ROOM_WIDTH, ROOM_HEIGHT);
	n_doors_max = MAX_CONNECTED_R;

	this->floorInstance = floorInstance;
	this->wallInstance = wallInstance;

	//mappe
	for(int i = 0; i < size.x * size.y; i++) {
		physical[i] = NULL;
		characters[i] = NULL;
	}

	//porte
	for(int i = 0; i < n_doors_max; i++) {
		doors[i] = NULL;
	}
	door_positions[0] = Coordinate(size.x / 2, 0);
	door_positions[1] = Coordinate(0, size.y / 2);
	door_positions[2] = Coordinate(size.x / 2, size.y - 1);
	door_positions[3] = Coordinate(size.x - 1, size.y / 2);
}
void Map::destroy() {
	Coordinate i(0, 0, size);
	do {
		physical[i.single()]->destroy();
		i.next();
	} while(!i.equals(Coordinate(0, 0)));
	wallInstance->destroy();
	floorInstance->destroy();
	delete this;
}
void Map::update_all(char input) {
	Coordinate i(0, 0, size);
	do {
		int points = 0;
		physical[i.single()]->update(this, input);
		i.next();
	} while(!i.equals(Coordinate(0, 0)));
}

#pragma region AUSILIARIE
	Coordinate Map::getDoorEntrance(Coordinate doorCenter) {
		Coordinate res;
		int d = 0;
		while(d < DIR_TOT) {
			if(!Coordinate(doorCenter, DIRECTIONS[d]).inBounds(Coordinate(0, 0), size))
				res = Coordinate(doorCenter, DIRECTIONS[d].getNegative());
			else d++;
		}
		return res;
	}
#pragma region GENERATION
	void Map::generate()
	{
		pUnionFind sets = new UnionFind();
		//GENERA MURI LATERALI
		generateSidesWalls();
		//GENERA PORTE
		//CREA STANZA NELLA STANZA (QUADRATO VUOTO AL CENTRO)
		generateInnerRoom();
		//RIEMPI LA STANZA DI MURI E CORRIDOI
		generateAllPaths(sets);
		//FAI IN MODO CHE OGNI PUNTO SIA RAGGIUNGIBILE DA OGNI ALTRO PUNTO
		connectPaths(sets);
		//RIDIMENSIONA LA STANZA, OVVERO ESEGUI UN ALLARGAMENTO DI "X_SCALE" VOLTE
		resizeMap();
	}
	void Map::generate_with_doors()
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

#pragma region AUSILIARIE_PRINCIPALI
	void Map::generateSidesWalls() {
		for(int y = 0; y < size.y; y++) {
			int delta_x = 1;
			if(y != 0 && y != size.y - 1) delta_x = ROOM_WIDTH_T - 1;
			for(int x = 0; x < ROOM_WIDTH_T; x += delta_x) physical[Coordinate(x, y).single()] = wallInstance;
		}
	}
	void Map::generateInnerRoom() {
		Coordinate rstart((ROOM_WIDTH_T - CENTRAL_ROOM_SIZE) / 2, (ROOM_HEIGHT - CENTRAL_ROOM_SIZE) / 2), rend((ROOM_HEIGHT + CENTRAL_ROOM_SIZE) / 2., (ROOM_WIDTH_T + CENTRAL_ROOM_SIZE) / 2);
		Coordinate i(rstart, rstart, rend);
		do {
			physical[i.single()] = floorInstance;
			i.next();
		} while(!i.equals(rstart));
	}
	void Map::generateAllPaths(pUnionFind sets) {
		Coordinate rand_p = Coordinate();
		rand_p.setMatrix(size);
		rand_p.randomize(0, size.x, 0, size.y);
		for(int i = 0; i < size.y * size.x; i++) {
			rand_p.next();
			if(physical[rand_p.single()] == NULL) {
				sets->makeSet(rand_p.single());
				generatePath(rand_p, sets);
			}
		}
	}
	
	void Map::connectPaths(pUnionFind sets) {
		s_coord currentSet = sets->firstSet();

		while(sets->getNumber() > 1) {
			bool hasConnected = false;
			int distance = 1;

			//TROVA I MURI ADIACENTI AL SET
			//s_coord currentSet = sets->getNth(rand() % sets->getNumber());
			currentSet = sets->find(currentSet);
			Coordinate adjacentWalls[ROOM_AREA_T], borderWalls[ROOM_AREA_T];
			int breakDirections[ROOM_AREA_T];
			int adjacentWalls_n = getAdjacentWalls(adjacentWalls, currentSet), borderWalls_n = 0;

			//FINCHÉ NON HA CONNESSO QUALCOSA, CERCA SET CHE CONFININO A UNA DETERMINATA DISTANZA OPPURE AUMENTA LA DISTANZA
			while(!hasConnected) {
				//OTTIENI I MURI DI CONFINE TRA DUE SET DIVERSI
				borderWalls_n = getBorderWalls(borderWalls, breakDirections, adjacentWalls, adjacentWalls_n, *sets, currentSet, distance);

				//SE NE HA TROVATI: CONNETTI (ROMPI IL MURO/I MURI)
				if(borderWalls_n != 0) {
					//ROMPI UN MURO A CASO TRA QUELLI TROVATI
					int r = rand() % borderWalls_n, brokenWall = 0;
					while(r > 0) {
						if(adjacentWalls[brokenWall].x != -1 && adjacentWalls[brokenWall].y != -1) r--;
						brokenWall++;
					}
					Coordinate bw = borderWalls[brokenWall];
					
					//ROMPI distance MURI A PARTIRE DA QUELLO, NELLA GIUSTA DIREZIONE
					for(int dist = 0; dist <= distance; dist++) {
						Coordinate dir = DIRECTIONS[breakDirections[brokenWall]];
						Coordinate tw = Coordinate(bw, dir.getTimes(dist, dist));
						physical[tw.single()] = floorInstance;
						sets->merge(currentSet, tw.single());
					}

					hasConnected = true;
				}
				//ALTRIMENTI CERCA A UNA DISTANZA MAGGIORE
				else
					distance++;
			}
		}
	}
	void Map::resizeMap() {
		for(int y = 0; y < ROOM_HEIGHT; y++) {
			for(int x = ROOM_WIDTH_T - 1; x >= 0; x++) {
				for(int s = 0; s < SCALE_X; s++)
					physical[Coordinate(x * scale_x + s, y).single()] = physical[Coordinate(x, y).single()];
			}
		}
	}
	void Map::generateDoors(pUnionFind sets) {
		for(int door = 0; door < n_doors_sides; door++) {
			Coordinate door_pos = doors[door]->getPosition();
			door_pos.setMatrix(size);
			physical[door_pos.single()] = doors[door];
			sets->makeSet(door_pos.single());
		}
	}
#pragma endregion AUSILIARIE_PRINCIPALI
#pragma endregion AUSILIARIE


#pragma endregion GENERATION


#pragma region CHECK_SET_GET
//// CHECK POSITION
	pPhysical Map::checkPosition(Coordinate pos) {
		if(pos.inBounds(Coordinate(0, 0), size) && physical[pos.single()]->getId() != ID_FLOOR)
			return physical[pos.single()];
		else return NULL;
	}
	pCharacter Map::checkCharacter(Coordinate pos) {
		if(pos.inBounds(Coordinate(0, 0), size) && characters[pos.single()] != NULL)
			return characters[pos.single()];
		else return NULL;
	}
	pChest Map::checkChest(Coordinate pos) {
		if(pos.inBounds(Coordinate(0, 0), size) && chests[pos.single()] != NULL)
			return chests[pos.single()];
		else return NULL;
	}
	pDoor Map::checkDoor(Coordinate pos) {
		if(pos.inBounds(Coordinate(0, 0), size) && physical[pos.single()]->getId() == ID_DOOR)
			return getDoorInPosition(pos);
		else return NULL;
	}

//// CHECK LINE
	pPhysical Map::checkLine(Coordinate start, Coordinate end) {
		Coordinate delta = Coordinate(end, start.getNegative());
		int deltaMax = delta.x;
		if(delta.y > delta.x) deltaMax = delta.y;
		delta.times(1. / deltaMax, 1. / deltaMax);

		Coordinate i = start;
		pPhysical target = NULL;
		while(!i.equals(end) && target == NULL) {
			target = checkPosition(i);
			i = Coordinate(i, delta);
		}
		if(target == NULL) return checkPosition(end);
		else return NULL;
	}
	pCharacter Map::checkLineCharacter(Coordinate start, Coordinate end) {
		Coordinate delta = Coordinate(end, start.getNegative());
		int deltaMax = delta.x;
		if(delta.y > delta.x) deltaMax = delta.y;
		delta.times(1. / deltaMax, 1. / deltaMax);

		Coordinate i = start;
		pCharacter target = NULL;
		while(!i.equals(end) && target == NULL) {
			target = checkCharacter(i);
			i = Coordinate(i, delta);
		}
		if(target == NULL) return checkCharacter(end);
		else return NULL;
	}

//// BOOL
	bool Map::isFreeSpace(Coordinate start, Coordinate end) {
		Coordinate i = Coordinate(start, start, Coordinate(start, end));
		bool allowed = true;
		do {
			if(physical[i.single()]->getId() != ID_FLOOR) allowed = false;
			else i.next();
		} while(allowed && !i.equals(start));
		return allowed;
	}
	bool Map::isLegalMove(pPhysical obj, Coordinate target) {
		Coordinate i = Coordinate(target, target, Coordinate(target, obj->getSize()));
		bool allowed = true;
		do {
			if(physical[i.single()]->getId() != ID_FLOOR && physical[i.single()] != obj) allowed = false;
			else i.next();
		} while(allowed && !i.equals(target));
		return allowed;
	}

//// GET
	Coordinate Map::getSize() {
		return size;
	}
	int Map::get_n_doors_max() {
		return n_doors_max;
	}
	pDoor Map::getDoorInPosition(Coordinate pos) {
		bool found = false;
		int d = 0;
		while(!found && d < MAX_CONNECTED_R) {
			if(doors[d]->getPosition().equals(pos)) found = true;
			else d++;
		}
		if(!found) return NULL;
		else return doors[d];
	}

//// EDIT
	void Map::addDoor(int dir, lock_type lt) {
		if(doors[dir] == NULL) doors[dir] = new Door(door_positions[dir], getDoorEntrance(door_positions[dir]), lt);
	}
	void Map::addCharacter(pCharacter character) {

	}
	bool Map::move(pPhysical obj, Coordinate target) {
		if(!obj->isInanimate() && obj->getPosition().inBounds(Coordinate(0, 0), size) && isLegalMove(obj, target)) {
			//SPOSTA
			Coordinate i = Coordinate(target, target, Coordinate(target, obj->getSize()));
			do {
				physical[i.single()] = physical[obj->getPosition().single()];
				characters[i.single()] = characters[obj->getPosition().single()];
				chests[i.single()] = chests[obj->getPosition().single()];
				i.next();
			} while(!i.equals(target));
			//RIMUOVI CASELLE VECCHIE (NON PIÙ OCCUPATE)
			i = Coordinate(obj->getPosition(), obj->getPosition(), Coordinate(obj->getPosition(), obj->getSize()));
			do {
				if(!i.inBounds(target, Coordinate(target, obj->getSize()))) {
					physical[i.single()] = floorInstance;
					characters[i.single()] = NULL;
					chests[i.single()] = NULL;
				}
				i.next();
			} while (!i.equals(obj->getPosition()));
			return true;
		} else return false;
	}
	void Map::remove(pPhysical obj) {
		if(!obj->isInanimate()) {
			Coordinate i = Coordinate(obj->getPosition(), obj->getPosition(), Coordinate(obj->getPosition(), obj->getSize()));
			do {
				physical[i.single()] = floorInstance;
				characters[i.single()] = NULL;
				chests[i.single()] = NULL;
				i.next();
			} while(!i.equals(obj->getPosition()));
		}
	}
#pragma endregion CHECK_SET_GET