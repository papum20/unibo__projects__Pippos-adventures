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

int Map::shortestPath(Coordinate path[ROOM_AREA], Coordinate A, Coordinate B, pPhysical obj = NULL) {
	if(A.equals(B) || !A.inBounds(Coordinate(0, 0), size)) return 0;
	else {
		int length = 0;
		Coordinate prev[ROOM_AREA];				//ogni cella contiene quella da cui si proviene (per il percorso più breve)
		int dist[ROOM_AREA];					//distanza (più breve) di ogni cella da A
		QueueCoordinate Q = QueueCoordinate();	//posizioni da cui visitare quelle adiacenti

		for(int i = 0; i < ROOM_AREA; i++) dist[i] = -1;
		dist[A.single()] = 0;
		Q.push(A);

		bool reached = false;
		do {
			Coordinate cur = Q.pop();
			if(cur.equals(B)) reached = true;
			else {
				for(int d = 0; d < DIRECTIONS_N; d++) {
					Coordinate nxt = Coordinate(cur, DIRECTIONS[d]);
					if(dist[nxt.single()] == -1 && ((obj == NULL && physical[nxt.single()]->getId() == ID_FLOOR) || isLegalMove(obj, nxt)) ) {
						prev[nxt.single()] = cur;
						dist[nxt.single()] = dist[cur.single()] + 1;
						Q.push(nxt);
						length = dist[nxt.single()];
					}
				}
			}
		} while(!reached && !Q.isEmpty());

		if(dist[B.single()] != -1) {
			path[length - 1] = B;
			for(int i = length - 1; i > 0; i--) path[i - 1] = prev[path[i].single()];
			Q.destroy();
			return length;
		} else return -1;
	}
}
int Map::shortestPath_physical(Coordinate path[ROOM_AREA], pPhysical A, pPhysical B, int dist_min = 1, int dist_max = 1) {
	if(A == NULL || B == NULL) return 0;
	else {
		if(dist_min < 1) dist_min = 1;
		if(dist_max < dist_min) dist_max = dist_min;

		int length = 0;
		Coordinate prev[ROOM_AREA];				//ogni cella contiene quella da cui si proviene (per il percorso più breve)
		int dist[ROOM_AREA];					//distanza (più breve) di ogni cella da A
		QueueCoordinate Q = QueueCoordinate();	//posizioni da cui visitare quelle adiacenti
		
		for(int i = 0; i < ROOM_AREA; i++) dist[i] = -1;
		dist[A->getPosition().single()] = 0;
		Q.push(A->getPosition());

		bool reached = false;
		Coordinate res;
		do {
			Coordinate start = Q.pop();							//vertice in basso a sinistra occupato dall'oggetto
			Coordinate end = Coordinate(start, A->getSize());	//vertice in alto a destra
			if(	//controlla i rettangoli in tutte le direzioni (cioè controlla di trovare B nel rettangolo lungo dist_max e non in quello lungo dist_min)
				(findRectangle(B, Coordinate(start, DIRECTIONS[DIRECTION_DOWN]), Coordinate(end.x, start.y + dist_max)) && !findRectangle(B, Coordinate(start, DIRECTIONS[DIRECTION_DOWN]), Coordinate(end.x, start.y + dist_min - 1))) ||	//basso
				(findRectangle(B, Coordinate(start.x - 1, end.y), Coordinate(start.x - dist_max, start.y)) 				&& !findRectangle(B, Coordinate(start.x - 1, end.y), Coordinate(start.x - dist_min + 1, start.y))) 				||	//sinistra
				(findRectangle(B, Coordinate(end, DIRECTIONS[DIRECTION_UP]), Coordinate(start.x, end.y - dist_max) )	&& !findRectangle(B, Coordinate(end, DIRECTIONS[DIRECTION_UP]), Coordinate(start.x, end.y - dist_min + 1)))		||	//alto
				(findRectangle(B, Coordinate(end.x + 1, start.y), Coordinate(end.x + dist_max, end.y)) 					&& !findRectangle(B, Coordinate(end.x + 1, start.y), Coordinate(end.x + dist_min - 1, end.y)))						//destra
			) {
				reached = true;
				res = start;
			}
			else {
				for(int d = 0; d < DIRECTIONS_N; d++) {
					Coordinate nxt = Coordinate(start, DIRECTIONS[d]);
					if(dist[nxt.single()] == -1 && isLegalMove(A, nxt)) {
						prev[nxt.single()] = start;
						dist[nxt.single()] = dist[start.single()] + 1;
						Q.push(nxt);
						length = dist[nxt.single()];
					}
				}
			}
		} while(!reached && !Q.isEmpty());

		if(reached) {
			path[length - 1] = res;
			for(int i = length - 1; i > 0; i--) path[i - 1] = prev[path[i].single()];
			Q.destroy();
			return length;
		} else return -1;
	}
}

int Map::vision(pPhysical obj[ROOM_AREA], Coordinate source, int range = -1) {
	//IMPLEMENTAZIONE: "spara" raggi da source verso tutti i punti del muro di perimetro, con entrambe le implementazioni checkLine_floor e checkLine_ceil; ritorna l'intersezione dei risultati
	int length = 0;
	pPhysical obj_floor[ROOM_AREA], obj_ceil[ROOM_AREA];
	int len_floor = 0, len_ceil = 0;
	//"spara" raggi
	Coordinate target = Coordinate(0, 0, size);
	do {
		//cerca physical
		pPhysical tmp_floor[ROOM_AREA], tmp_ceil[ROOM_AREA];
		int len_floor_t = checkLine(tmp_floor, source, target);
		int len_ceil_t = checkLine_ceil(tmp_ceil, source, target);
		//aggiungi quelli che non erano già stati trovati
		for(int i = 0; i < len_floor_t; i++) {
			if(!tmp_floor[i]->findInArray(obj_floor, len_floor)) {
				obj_floor[len_floor] = tmp_floor[i];
				len_floor++;
			}
		}
		for(int i = 0; i < len_ceil_t; i++) {
			if(!tmp_ceil[i]->findInArray(obj_ceil, len_ceil)) {
				obj_ceil[len_ceil] = tmp_ceil[i];
				len_ceil++;
			}
		}
		//next
		if(target.x == 0 && target.y != 0 && target.y != size.y - 1) target.x = size.x - 1;
		else target.next();
	} while(!target.equals(Coordinate(0, 0)));
	//intersezione
	for(int i = 0; i < len_floor; i++) {
		if(obj_floor[i]->findInArray(obj_ceil, len_ceil)) {
			obj[length] = obj_floor[i];
			length++;
		}
	}
	return length;
}



#pragma region AUSILIARIE
	void Map::addLineToCheck(pPhysical obj[ROOM_AREA], int &found, Coordinate start, Coordinate end) {
		int added = 0;
		pPhysical line[ROOM_AREA];
		int len = checkLine(line, start, end);
		for(int i = 0; i < len; i++) {
			if(!line[i]->findInArray(obj, found)) {
				obj[found + i] = line[i];
				added++;
			}
		}
		found += added;
	}
	Coordinate Map::checkLine_floor_next(Coordinate i, Coordinate delta) {
		Coordinate j = Coordinate(i, delta);
		Coordinate t1 = Coordinate(i.x, j.y);
		Coordinate t2 = Coordinate(j.x, i.y);
		if(physical[t1.single()]->getId() == ID_WALL && physical[t2.single()]->getId() == ID_WALL) return COORDINATE_ERROR;
		else return j;
	}
	Coordinate Map::checkLine_ceil_next(Coordinate i, Coordinate delta) {
		Coordinate j = Coordinate(i, delta);
		Coordinate t1 = Coordinate(i.x, j.y);
		Coordinate t2 = Coordinate(j.x, i.y);
		if(physical[t1.single_ceil()]->getId() == ID_WALL && physical[t2.single_ceil()]->getId() == ID_WALL) return COORDINATE_ERROR;
		else return j;
	}
	Coordinate Map::getDoorEntrance(Coordinate door_pos) {
		Coordinate res;
		int d = 0;
		while(d < DIRECTIONS_N) {
			if(!Coordinate(door_pos, DIRECTIONS[d]).inBounds(Coordinate(0, 0), size))
				res = Coordinate(door_pos, DIRECTIONS[d].negative());
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
						Coordinate tw = Coordinate(bw, dir.times(dist, dist));
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
	int Map::checkLine(pPhysical obj[ROOM_AREA], Coordinate start, Coordinate end) {
		int found = 0;
		Coordinate delta = Coordinate::unitVector(start, end);

		Coordinate i = start;
		bool ended = false;
		while(!ended) {
			obj[found] = checkPosition(i);
			//prima di aggiungerlo (incrementando found) controlla 1.di aver trovato qualcosa
			//2.di non averlo già inserito (per far ciò basta controllare l'ultimo inserito, perché gli oggetti, essendo rettangolari, non possono averne un altro "in mezzo", controllando in questo ordine)
			if(obj[found] != NULL && (found == 0 || obj[found - 1] != obj[found])) found++;
			if(i.equals_int(end)) ended = true;
			else {
				i = checkLine_floor_next(i, delta);
				if(i.equals(COORDINATE_ERROR)) ended = true;
			}
		}
		return found;
	}
	//IMPLEMENTATO COME CHECKLINE, CAMBIA ARROTONDAMENTO
	int Map::checkLine_ceil(pPhysical obj[ROOM_AREA], Coordinate start, Coordinate end) {
		int found = 0;
		Coordinate delta = Coordinate::unitVector(start, end);

		Coordinate i = start;
		bool ended = false;
		while(!ended) {
			obj[found] = checkPosition(i);
			//prima di aggiungerlo (incrementando found) controlla 1.di aver trovato qualcosa
			//2.di non averlo già inserito (per far ciò basta controllare l'ultimo inserito, perché gli oggetti, essendo rettangolari, non possono averne un altro "in mezzo", controllando in questo ordine)
			if(obj[found] != NULL && (found == 0 || obj[found - 1] != obj[found])) found++;
			if(i.equals_int(end)) ended = true;
			else {
				i = checkLine_ceil_next(i, delta);
				if(i.equals(COORDINATE_ERROR)) ended = true;
			}
		}
		return found;
	}
	//IMPLEMENTATO COME CHECKLINE, CAMBIA TIPO DI RIORNO
	int Map::checkLine_character(pCharacter obj[ROOM_AREA], Coordinate start, Coordinate end) {
		int found = 0;
		Coordinate delta = Coordinate::unitVector(start, end);

		Coordinate i = start;
		bool ended = false;
		while(!ended) {
			obj[found] = checkCharacter(i);
			if(obj[found] != NULL && (found == 0 || obj[found - 1] != obj[found])) found++;
			if(i.equals(end)) ended = true;
			else {
				i = checkLine_floor_next(i, delta);
				if(i.equals(COORDINATE_ERROR)) ended = true;
			}
		}
		return found;
	}

//// CHECK RECTANGLE
	int Map::checkRectangle(pPhysical obj[ROOM_AREA], Coordinate start, Coordinate end) {
		int found = 0;
		Coordinate A = start;
		while(A.y <= end.y) {
			addLineToCheck(obj, found, A, Coordinate(end.x, A.y));
			A.y++;
		}
		return found;
	}

//// FIND
	bool Map::findLine(pPhysical obj, Coordinate start, Coordinate end) {
		//si potrebbe implementare semplicemente chiamando checkline e cercando nell'array, ma almeno così se trova l'oggetto si può fermare subito
		Coordinate delta = Coordinate::unitVector(start, end);

		Coordinate i = start;
		bool ended = false;
		while(!ended) {
			if(checkPosition(i) == obj) ended = true;
			if(i.equals(end)) ended = true;
			else {
				i = checkLine_floor_next(i, delta);
				if(i.equals(COORDINATE_ERROR)) ended = true;
			}
		}
		return checkPosition(i) == obj;
	}
	bool Map::findRectangle(pPhysical obj, Coordinate start, Coordinate end) {
		//si potrebbe implementare semplicemente chiamando checkrectangle e cercando nell'array, ma almeno così se trova l'oggetto si può fermare subito
		bool found = false;
		if(start.lessEqual(end) || end.lessEqual(start)) {
			//riga per riga
			Coordinate A = start;
			if(start.lessEqual(end)) {	//basso
				while(!found && A.y <= end.y) {
					found = findLine(obj, A, Coordinate(end.x, A.y));
					A.y++;
				}
			} else {					//alto
				while(!found && A.y >= end.y) {
					found = findLine(obj, A, Coordinate(end.x, A.y));
					A.y--;
				}
			}
		} else {
			//colonna per colonna
			Coordinate A = start;
			if(start.x <= end.x) {		//destra
				while(!found && A.x <= end.x) {
					found = findLine(obj, A, Coordinate(A.x, end.y));
					A.x++;
				}
			} else {					//sinistra
				while(!found && A.x >= end.x) {
					found = findLine(obj, A, Coordinate(A.x, end.y));
					A.x--;
				}
			}
		}
		return found;
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