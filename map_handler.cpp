#include "map_handler.hpp"


MapHandler::MapHandler() {

}

#pragma region PATH_FINDING
	int MapHandler::shortestPath(pMap map, Coordinate path[ROOM_AREA], Coordinate A, Coordinate B, pPhysical obj) {
		if(A.equals(B) || !A.inBounds(Coordinate(0, 0), map->size)) return 0;
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
						if(dist[nxt.single()] == -1 && ((obj == NULL && map->physical[nxt.single()]->getId() == ID_FLOOR) || isLegalMove(map, obj, nxt)) ) {
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
	int MapHandler::shortestPath_physical(pMap map, Coordinate path[ROOM_AREA], pPhysical A, pPhysical B, int dist_min, int dist_max) {
		if(A == NULL || B == NULL) return 0;
		else {
			if(dist_min < 1) dist_min = 1;
			if(dist_max < dist_min) dist_max = dist_min;

			int length = 0;
			Coordinate prev[ROOM_AREA];				//ogni cella contiene quella da cui si proviene (per il percorso più breve)
			int dist[ROOM_AREA];					//distanza (più breve) di ogni cella da A
			QueueCoordinate Q = QueueCoordinate();	//posizioni da cui visitare quelle adiacenti
			
			for(int i = 0; i < ROOM_AREA; i++) dist[i] = -1;
			dist[A->getPosition().single_set(map->size)] = 0;
			Q.push(A->getPosition());

			bool reached = false;
			Coordinate res;
			do {
				Coordinate start = Q.pop();							//vertice in basso a sinistra occupato dall'oggetto
				Coordinate end = Coordinate(start, A->getSize());	//vertice in alto a destra
				if(	//controlla i rettangoli in tutte le direzioni (cioè controlla di trovare B nel rettangolo lungo dist_max e non in quello lungo dist_min)
					(findRectangle(map, B, Coordinate(start, DIRECTIONS[DIRECTION_DOWN]), Coordinate(end.x, start.y + dist_max))	&& (dist_min == 1 || !findRectangle(map, B, Coordinate(start, DIRECTIONS[DIRECTION_DOWN]), Coordinate(end.x, start.y + dist_min - 1))) 	) ||	//basso
					(findRectangle(map, B, Coordinate(start.x - 1, end.y), Coordinate(start.x - dist_max, start.y)) 				&& (dist_min == 1 || !findRectangle(map, B, Coordinate(start.x - 1, end.y), Coordinate(start.x - dist_min + 1, start.y))) 				) ||	//sinistra
					(findRectangle(map, B, Coordinate(end, DIRECTIONS[DIRECTION_UP]), Coordinate(start.x, end.y - dist_max) )		&& (dist_min == 1 || !findRectangle(map, B, Coordinate(end, DIRECTIONS[DIRECTION_UP]), Coordinate(start.x, end.y - dist_min + 1)))		) ||	//alto
					(findRectangle(map, B, Coordinate(end.x + 1, start.y), Coordinate(end.x + dist_max, end.y)) 					&& (dist_min == 1 || !findRectangle(map, B, Coordinate(end.x + 1, start.y), Coordinate(end.x + dist_min, end.y)))						)		//destra
				) {
					reached = true;
					res = start;
				}
				else {
					for(int d = 0; d < DIRECTIONS_N; d++) {
						Coordinate nxt = Coordinate(start, DIRECTIONS[d]);
						nxt.setMatrix(map->size);
						if(dist[nxt.single()] == -1 && isLegalMove(map, A, nxt)) {
							prev[nxt.single()] = start;
							dist[nxt.single()] = dist[start.single_set(map->size)] + 1;
							Q.push(nxt);
							length = dist[nxt.single()];
						}
					}
				}
			} while(!reached && !Q.isEmpty());

			if(reached) {
				if(length > 0) {
					path[length - 1] = res;
					for(int i = length - 1; i > 0; i--) path[i - 1] = prev[path[i].single()];
				}
				Q.destroy();
				return length;
			} else return -1;
		}
	}

	int MapHandler::vision(pMap map, pPhysical obj[ROOM_AREA], Coordinate source, int range) {
		//IMPLEMENTAZIONE: "spara" raggi da source verso tutti i punti del muro di perimetro, con entrambe le implementazioni checkLine_floor e checkLine_ceil; ritorna l'intersezione dei risultati
		int length = 0;
		pPhysical obj_floor[ROOM_AREA], obj_ceil[ROOM_AREA];
		int len_floor = 0, len_ceil = 0;
		//"spara" raggi
		Coordinate target = Coordinate(0, 0, map->size);
		do {
			//cerca physical
			pPhysical tmp_floor[ROOM_AREA], tmp_ceil[ROOM_AREA];
			int len_floor_t = checkLine(map, tmp_floor, source, target);
			int len_ceil_t = checkLine_ceil(map, tmp_ceil, source, target);
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
			if(target.x == 0 && target.y != 0 && target.y != map->size.y - 1) target.x = map->size.x - 1;
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
#pragma endregion PATH_FINDING



#pragma region CHECK
//// CHECK POSITION
	pPhysical MapHandler::checkPosition(pMap map, Coordinate pos) {
		pos.setMatrix(map->size);
		if(pos.inBounds(Coordinate(0, 0), map->size) && map->physical[pos.single()]->getId() != ID_FLOOR)
			return map->physical[pos.single()];
		else return NULL;
	}
	pCharacter MapHandler::checkCharacter(pMap map, Coordinate pos) {
		pos.setMatrix(map->size);
		if(pos.inBounds(Coordinate(0, 0), map->size) && map->characters[pos.single()] != NULL)
			return map->characters[pos.single()];
		else return NULL;
	}
	pAlive MapHandler::checkAlive(pMap map, Coordinate pos) {
		return checkCharacter(map, pos);
	}
	pChest MapHandler::checkChest(pMap map, Coordinate pos) {
		pos.setMatrix(map->size);
		if(pos.inBounds(COORDINATE_ZERO, map->size) && map->chests[pos.single()] != NULL)
			return map->chests[pos.single()];
		else return NULL;
	}
	pDoor MapHandler::checkDoor(pMap map, Coordinate pos) {
		pos.setMatrix(map->size);
		if(pos.inBounds(Coordinate(0, 0),map->size) && map->physical[pos.single()]->getId() == ID_DOOR)
			return getDoorInPosition(map, pos);
		else return NULL;
	}

//// CHECK LINE
	int MapHandler::checkLine(pMap map, pPhysical obj[ROOM_AREA], Coordinate start, Coordinate end) {
		int found = 0;
		Coordinate delta = Coordinate::unitVector(start, end);

		Coordinate i = start;
		bool ended = false;
		while(!ended && i.inBounds(COORDINATE_ZERO, map->size)) {
			obj[found] = checkPosition(map, i);
			//prima di aggiungerlo (incrementando found) controlla 1.di aver trovato qualcosa
			//2.di non averlo già inserito (per far ciò basta controllare l'ultimo inserito, perché gli oggetti, essendo rettangolari, non possono averne un altro "in mezzo", controllando in questo ordine)
			if(obj[found] != NULL && (found == 0 || obj[found - 1] != obj[found])) found++;
			if(i.equals_int(end)) ended = true;
			else {
				i = checkLine_floor_next(map, i, delta);
				if(i.equals(COORDINATE_ERROR)) ended = true;
			}
		}
		return found;
	}
	//IMPLEMENTATO COME CHECKLINE, CAMBIA ARROTONDAMENTO
	int MapHandler::checkLine_ceil(pMap map, pPhysical obj[ROOM_AREA], Coordinate start, Coordinate end) {
		int found = 0;
		Coordinate delta = Coordinate::unitVector(start, end);

		Coordinate i = start;
		bool ended = false;
		while(!ended && i.inBounds(COORDINATE_ZERO, map->size)) {
			obj[found] = checkPosition(map, i);
			//prima di aggiungerlo (incrementando found) controlla 1.di aver trovato qualcosa
			//2.di non averlo già inserito (per far ciò basta controllare l'ultimo inserito, perché gli oggetti, essendo rettangolari, non possono averne un altro "in mezzo", controllando in questo ordine)
			if(obj[found] != NULL && (found == 0 || obj[found - 1] != obj[found])) found++;
			if(i.equals_int(end)) ended = true;
			else {
				i = checkLine_ceil_next(map, i, delta);
				if(i.equals(COORDINATE_ERROR)) ended = true;
			}
		}
		return found;
	}
	//IMPLEMENTATO COME CHECKLINE, CAMBIA TIPO DI RIORNO
	int MapHandler::checkLine_character(pMap map, pCharacter obj[ROOM_AREA], Coordinate start, Coordinate end) {
		int found = 0;
		Coordinate delta = Coordinate::unitVector(start, end);

		Coordinate i = start;
		bool ended = false;
		while(!ended && i.inBounds(COORDINATE_ZERO, map->size)) {
			obj[found] = checkCharacter(map, i);
			if(obj[found] != NULL && (found == 0 || obj[found - 1] != obj[found])) found++;
			if(i.equals(end)) ended = true;
			else {
				i = checkLine_floor_next(map, i, delta);
				if(i.equals(COORDINATE_ERROR)) ended = true;
			}
		}
		return found;
	}

//// CHECK RECTANGLE
	int MapHandler::checkRectangle(pMap map, pPhysical obj[ROOM_AREA], Coordinate start, Coordinate end) {
		int found = 0;
		Coordinate A = start;
		while(A.y <= end.y) {
			addLineToCheck(map, obj, found, A, Coordinate(end.x, A.y));
			A.y++;
		}
		return found;
	}

//// FIND
	bool MapHandler::findLine(pMap map, pPhysical obj, Coordinate start, Coordinate end) {
		//si potrebbe implementare semplicemente chiamando checkline e cercando nell'array, ma almeno così se trova l'oggetto si può fermare subito
		Coordinate delta = Coordinate::unitVector(start, end);

		Coordinate i = start;
		bool ended = false;
		while(!ended) {
			if(checkPosition(map, i) == obj) ended = true;
			if(i.equals(end)) ended = true;
			else {
				i = checkLine_floor_next(map, i, delta);
				if(i.equals(COORDINATE_ERROR)) ended = true;
			}
		}
		return checkPosition(map, i) == obj;
	}
	bool MapHandler::findRectangle(pMap map, pPhysical obj, Coordinate start, Coordinate end) {
		//si potrebbe implementare semplicemente chiamando checkrectangle e cercando nell'array, ma almeno così se trova l'oggetto si può fermare subito
		bool found = false;
		if(start.lessEqual(end) || end.lessEqual(start)) {
			//riga per riga
			Coordinate A = start;
			if(start.lessEqual(end)) {	//basso
				while(!found && A.y <= end.y) {
					found = findLine(map, obj, A, Coordinate(end.x, A.y));
					A.y++;
				}
			} else {					//alto
				while(!found && A.y >= end.y) {
					found = findLine(map, obj, A, Coordinate(end.x, A.y));
					A.y--;
				}
			}
		} else {
			//colonna per colonna
			Coordinate A = start;
			if(start.x <= end.x) {		//destra
				while(!found && A.x <= end.x) {
					found = findLine(map, obj, A, Coordinate(A.x, end.y));
					A.x++;
				}
			} else {					//sinistra
				while(!found && A.x >= end.x) {
					found = findLine(map, obj, A, Coordinate(A.x, end.y));
					A.x--;
				}
			}
		}
		return found;
	}

#pragma endregion CHECK



#pragma region SET_GET

//// BOOL

	bool MapHandler::isLegalMove(pMap map, pPhysical obj, Coordinate target) {
		Coordinate i = Coordinate(target, map->size, target, Coordinate(target, obj->getSize()));
		bool allowed = true;
		do {
			if(checkPosition(map, i) != NULL && map->physical[i.single()] != obj) allowed = false;
			else i.next();
		} while(allowed && !i.equals(target));
		return allowed;
	}
	bool MapHandler::isFreeSpace(pMap map, Coordinate start, Coordinate size) {
		Coordinate i = Coordinate(start, map->size, start, Coordinate(start, size));
		bool allowed = true;
		do {
			if(!i.inBounds(COORDINATE_ZERO, map->size) || map->physical[i.single()]->getId() != ID_FLOOR) allowed = false;
			else i.next();
		} while(allowed && !i.equals(start));
		return allowed;
	}

//// GET
	pDoor MapHandler::getDoorInPosition(pMap map, Coordinate pos) {
		bool found = false;
		int d = 0;
		while(!found && d < MAX_CONNECTED_R) {
			if(map->doors[d]->getPosition().equals(pos)) found = true;
			else d++;
		}
		if(!found) return NULL;
		else return map->doors[d];
	}
/*	Coordinate MapHandler::getSize(pMap map) {
		returnmap->size;
	}
	int MapHandler::get_n_doors_max(pMap map) {
		return n_doors_max;
	}*/

//// EDIT
	bool MapHandler::move(pMap map, pPhysical obj, Coordinate target) {
		if(!obj->isInanimate() && obj->getPosition().inBounds(COORDINATE_ZERO, map->size) && isLegalMove(map, obj, target)) {
			//SPOSTA
			Coordinate i = Coordinate(target, map->size, target, Coordinate(target, obj->getSize()));
			do {
				map->physical[i.single()] = obj;
				if(obj->isCharacter()) map->characters[i.single()] = map->characters[obj->getPosition().single_set(map->size)];
				else if(obj->isProjectile()) map->projectiles[i.single()] = map->projectiles[obj->getPosition().single_set(map->size)];
				i.next();
			} while(!i.equals(target));
			//RIMUOVI CASELLE VECCHIE (NON PIÙ OCCUPATE)
			i = Coordinate(obj->getPosition(), map->size, obj->getPosition(), Coordinate(obj->getPosition(), obj->getSize()));
			do {
				if(!i.inBounds(target, Coordinate(target, obj->getSize()))) {
					map->physical[i.single()] = FLOOR_INSTANCE;
					map->characters[i.single()] = NULL;
					map->chests[i.single()] = NULL;
					map->projectiles[i.single()] = NULL;
				}
				i.next();
			} while (!i.equals(obj->getPosition()));
			
			obj->setPosition(target);
			return true;
		} else return false;
	}
	void MapHandler::remove(pMap map, pPhysical obj) {
		if(!obj->isInanimate() || obj->getId() == ID_CHEST) {
			Coordinate i = Coordinate(obj->getPosition(), map->size, obj->getPosition(), Coordinate(obj->getPosition(), obj->getSize()));
			do {
				map->physical[i.single()] = FLOOR_INSTANCE;
				map->characters[i.single()] = NULL;
				map->chests[i.single()] = NULL;
				map->projectiles[i.single()] = NULL;
				i.next();
			} while(!i.equals(obj->getPosition()));
		}
	}
	void MapHandler::addProjectile(pMap map, pProjectile projectile) {
		if(isFreeSpace(map, projectile->getPosition(), projectile->getSize())) {
			Coordinate i = Coordinate(projectile->getPosition(), map->size, projectile->getPosition(), Coordinate(projectile->getPosition(), projectile->getSize()));
			do {
				map->physical[i.single()] = projectile;
				map->projectiles[i.single()] = projectile;
				i.next();
			} while(!i.equals(projectile->getPosition()));
		}
	}
#pragma endregion SET_GET



#pragma region AUSILIARIE
	void MapHandler::addLineToCheck(pMap map, pPhysical obj[ROOM_AREA], int &found, Coordinate start, Coordinate end) {
		int added = 0;
		pPhysical line[ROOM_AREA];
		int len = checkLine(map, line, start, end);
		for(int i = 0; i < len; i++) {
			if(!line[i]->findInArray(obj, found)) {
				obj[found + i] = line[i];
				added++;
			}
		}
		found += added;
	}
	Coordinate MapHandler::checkLine_floor_next(pMap map, Coordinate i, Coordinate delta) {
		Coordinate j = Coordinate(i, delta);
		Coordinate t1 = Coordinate(i.x, j.y, map->size);
		Coordinate t2 = Coordinate(j.x, i.y, map->size);
		if(map->physical[t1.single()]->getId() == ID_WALL && map->physical[t2.single()]->getId() == ID_WALL) return COORDINATE_ERROR;
		else return j;
	}
	Coordinate MapHandler::checkLine_ceil_next(pMap map, Coordinate i, Coordinate delta) {
		Coordinate j = Coordinate(i, delta);
		Coordinate t1 = Coordinate(i.x, j.y, map->size);
		Coordinate t2 = Coordinate(j.x, i.y, map->size);
		if(map->physical[t1.single_ceil()]->getId() == ID_WALL && map->physical[t2.single_ceil()]->getId() == ID_WALL) return COORDINATE_ERROR;
		else return j;
	}
#pragma endregion AUSILIARIE