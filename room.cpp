#include "room.hpp"


#pragma region MAIN
	Room::Room(Coordinate pos) {
		//inzializza stanza
		this->pos = pos;
		scale = Coordinate(SCALE_X, SCALE_Y);
		size_t = Coordinate(ROOM_WIDTH_T, ROOM_HEIGHT_T);
		size = size_t.times(scale);

		map = new Map;
		map->size = size;
		//mappe
		for(int i = 0; i < size.x * size.y; i++) {
			map->physical[i] = NULL;
			map->characters[i] = NULL;
			map->chests[i] = NULL;
			map->projectiles[i] = NULL;
		}
	}
	void Room::recursiveDestroy() {
		Coordinate i(0, 0, size);
		do {
			pPhysical obj = map->physical[i.single()];
			if(obj != NULL && obj->getId() != ID_WALL && obj->getId() != ID_FLOOR) map->physical[i.single()]->destroy(map);
			i.next();
		} while(!i.equals(COORDINATE_ZERO));
		delete map;
		delete this;
	}
	void Room::update(int input) {
		Coordinate i(0, 0, size);
		// setta tutti gli oggetti come non updated e non drawn
		do {
			map->physical[i.single()]->resetUpdate();
			i.next();
		} while(!i.equals(COORDINATE_ZERO));
		// chiama l'update di tutti
		do {
			map->physical[i.single()]->update(map);
			i.next();
		} while(!i.equals(COORDINATE_ZERO));
	}

	void Room::generate(bool c)
	{
		pUnionFind sets = new UnionFind();
		//GENERA MURI LATERALI
		generateSidesWalls();
		//GENERA PORTE
		//CREA STANZA NELLA STANZA (QUADRATO VUOTO AL CENTRO)
		generateInnerRoom(sets);
		//RIEMPI LA STANZA DI MURI E CORRIDOI
		generateAllPaths(sets);
		//FAI IN MODO CHE OGNI PUNTO SIA RAGGIUNGIBILE DA OGNI ALTRO PUNTO
		connectPaths(sets);
		//RIDIMENSIONA LA STANZA, OVVERO ESEGUI UN ALLARGAMENTO DI "X_SCALE" VOLTE
		resizeMap();
	}

	void Room::spawnEnemy(pEnemy enemy) {
		s_coord available[ROOM_AREA];
		int av_size = getFreeCells(available, enemy->getSize());
		if(av_size > 0) {
			enemy->setPosition(Coordinate(available[rand() % av_size], size));
			addCharacter(enemy);
		}
	}
	void Room::spawnChest(pChest chest) {
		s_coord available[ROOM_AREA];
		int av_size = getFreeCells(available, chest->getSize());
		if(av_size > 0) {
			chest->setPosition(Coordinate(available[rand() % av_size], size));
			addChest(chest);
		}
	}

	void Room::draw(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_size, Coordinate center) {
		//disegna dall'alto al basso, da sinistra a destra, così si mantiene la prospettiva quando un oggetto che si trova davanti ad un altro gli viene disegnato davanti
		Coordinate wstart = Coordinate(center.x - Math::ceil(win_size.x / 2.) + 1, center.y - Math::ceil(win_size.y / 2.) + 1);

		Coordinate scr_it = Coordinate(0, 0, win_size);									//iteratore su schermo
		do {
			Coordinate scr_reverse = Coordinate(scr_it.x, win_size.y - scr_it.y - 1);	//itera da sotto ma disegna da sopra
			Coordinate map_it = Coordinate(scr_reverse, wstart);						//iteratore su mappa

			if(map_it.inBounds(COORDINATE_ZERO, size)) {								//se il punto è nella mappa: disegna
				pPhysical obj = MapHandler::checkPosition(map, map_it);
				if(obj == NULL) FLOOR_INSTANCE->drawAtPosition(map, scr, wstart, win_size, map_it);			//disegna floor se è vuoto
				else if(obj->isFixed()) obj->drawAtPosition(scr, wstart, win_size, map_it);					//disegna wall/door
				else {																						//disegna animate/chest+floor
					obj->drawAtOwnPosition(scr, wstart, win_size);
					//else{ scr[scr_reverse.inty()][scr_reverse.intx()].edit('x',-1,-1,0);
						//WINDOW *w = newwin(10,10,1,10);
						//box(w,0,0);
						//obj->getCurrentAnimation();
						//mvwprintw(w,1,1,to_string(obj->getCurrentAnimation().size.x).append(" ").append(to_string(obj->getCurrentAnimation().size.y)).c_str());
						//wrefresh(w);
					//}
					if(obj->getId() != ID_DOOR) FLOOR_INSTANCE->drawAtPosition(map, scr, wstart, win_size, map_it);
				}
			} else												//altrimenti "cancella"/lascia uno spazio vuoto
				scr[scr_reverse.inty()][scr_reverse.intx()] = Cell(CHAR_OUTSIDE, COLOR_OUTSIDE_FG, COLOR_OUTSIDE_BG, CELL_NO_ATTR);
			scr_it.next();
		} while(!scr_it.equals(COORDINATE_ZERO));
	}
#pragma endregion MAIN



#pragma region AUSILIARIE

	int Room::getFreeCells(s_coord available[], Coordinate size) {
		int length = 0;
		Coordinate i = Coordinate(0, 0, this->size);
		do {
			if(MapHandler::isFreeSpace(map, i, size)) {
				available[length] = i.single();
				length++;
			}
			i.next();
		} while(!i.equals(COORDINATE_ZERO));
		return length;
	}
//// ADD
	void Room::addCharacter(pCharacter character) {
		Coordinate i = Coordinate(character->getPosition(), size, character->getPosition(), Coordinate(character->getPosition(), character->getSize()));
		do {
			map->physical[i.single()] = character;
			map->characters[i.single()] = character;
			i.next();
		} while(!i.equals(character->getPosition()));
	}
	void Room::addChest(pChest chest) {
		Coordinate i = Coordinate(chest->getPosition(), size, chest->getPosition(), Coordinate(chest->getPosition(), chest->getSize()));
		do {
			map->physical[i.single()] = chest;
			map->chests[i.single()] = chest;
			i.next();
		} while(!i.equals(chest->getPosition()));
	}


#pragma region GENERATION
	void Room::generateSidesWalls() {
		Coordinate i = Coordinate(COORDINATE_ZERO, size, COORDINATE_ZERO, size_t);
		do {
			map->physical[i.single()] = WALL_INSTANCE;
			if(i.x == 0 && i.y > 0 && i.y < size_t.y - 1) i.x = size_t.x - 1;
			else i.next();
		} while(!i.equals(COORDINATE_ZERO));
	}
	void Room::generateInnerRoom(pUnionFind sets) {
		Coordinate rstart = Coordinate((size_t.x - CENTRAL_ROOM_WIDTH_T) / 2, (size_t.y - CENTRAL_ROOM_HEIGHT_T) / 2), rend = Coordinate(rstart, Coordinate(CENTRAL_ROOM_WIDTH_T, CENTRAL_ROOM_HEIGHT_T));
		Coordinate i(rstart, size, rstart, rend);
		do {
			map->physical[i.single()] = FLOOR_INSTANCE;
			sets->makeSet(i.single());
			i.next();
		} while(!i.equals(i.start()));
	}
	void Room::generateAllPaths(pUnionFind sets) {
		Coordinate rand_start = Coordinate(COORDINATE_ZERO, size, COORDINATE_ZERO, size_t);
		rand_start.randomize(0, size_t.x, 0, size_t.y);
		Coordinate it = rand_start;
		do {			
			if(map->physical[it.single()] == NULL) {
				sets->makeSet(it.single());
				generatePath(it, sets);
			}
			it.next();
		} while(!it.equals(rand_start));
	}
	void Room::connectPaths(pUnionFind sets) {
		s_coord currentSet = sets->firstSet();

		while(sets->getNumber() > 1) {		//finché ci sono parti non connesse
			bool hasConnected = false;
			int distance = 1;

			//TROVA I MURI ADIACENTI AL SET
			currentSet = sets->find(currentSet);
			Coordinate adjacentWalls[ROOM_AREA_T];		//muri adiacenti al set
			int breakDirections[ROOM_AREA_T];			//direzione in cui rompere un muro per unire due set
			int adjacentWalls_n = getAdjacentWalls(adjacentWalls, *sets, currentSet), borderWalls_n = 0;

			//FINCHÉ NON HA CONNESSO QUALCOSA, CERCA SET CHE CONFININO A UNA DETERMINATA DISTANZA OPPURE AUMENTA LA DISTANZA
			while(!hasConnected) {
				//OTTIENI I MURI DI CONFINE TRA DUE SET DIVERSI
				borderWalls_n = getBorderWalls(adjacentWalls, breakDirections, adjacentWalls_n, *sets, currentSet, distance);

				//SE NE HA TROVATI: CONNETTI (ROMPI IL MURO/I MURI)
				if(borderWalls_n != 0) {
					//ROMPI UN MURO A CASO TRA QUELLI TROVATI
					int broken_ind = rand() % borderWalls_n;
					
					//ROMPI distance MURI A PARTIRE DA QUELLO, NELLA GIUSTA DIREZIONE
					Coordinate dir = DIRECTIONS[breakDirections[broken_ind]];
					for(int dist = 0; dist <= distance; dist++) {
						Coordinate broken = Coordinate(adjacentWalls[broken_ind], dir.times(dist, dist));
						broken.setMatrix(size);
						map->physical[broken.single()] = FLOOR_INSTANCE;
						sets->makeSet(broken.single());
						sets->merge(currentSet, broken.single());
					}
					hasConnected = true;
				}
				//ALTRIMENTI CERCA A UNA DISTANZA MAGGIORE
				else
					distance++;
			}
		}
	}
	void Room::resizeMap() {
		for(s_coord xy = size.x * size.y - 1; xy >= 0; xy--) {
			Coordinate xy_t = Coordinate(xy, size).times(1. / scale.x, 1. / scale.y);
			map->physical[xy] = map->physical[xy_t.single()];
		}
	}
	void Room::generatePath(Coordinate s, pUnionFind sets)
	{
		s.setMatrix(size);
		map->physical[s.single()] = FLOOR_INSTANCE;

		bool used_dirs[DIRECTIONS_N];	//direzioni usate
		int used_dirs_n;
		bool new_dirs[DIRECTIONS_N];	//nuove direzioni da generare
		int new_dirs_n;

		// CONTA DIREZIONI INUTILIZZABILI (PERCHÈ GIÀ USATE O FUORI DALLA MAPPA)
		int tot_chance = DIR_CHANCES[0];	//somma delle probabilità delle direzioni disponibili
		int unused_dirs_n = 0;
		for(int d = 0; d < DIRECTIONS_N; d++) {
			Coordinate nxt = Coordinate(Coordinate(s, DIRECTIONS[d]), size, COORDINATE_ZERO, size_t);
			if(nxt.inOwnBounds() && map->physical[nxt.single()] == NULL) {
				used_dirs[d] = false;
				unused_dirs_n++;
				tot_chance += DIR_CHANCES[unused_dirs_n];
			} else used_dirs[d] = true;
		}
		used_dirs_n = DIRECTIONS_N - unused_dirs_n;

		if(used_dirs_n != DIRECTIONS_N) {
			// SCEGLI NUMERO DI DIREZIONI DA GENERARE (TRA QUELLE DISPONIBILI)
			new_dirs_n = 0;
			int new_dirs_r = rand() % tot_chance;	//indice per generare un numero random di nuove direzioni
			int chance_counter = 0;
			while(new_dirs_r >= chance_counter + DIR_CHANCES[new_dirs_n]) {
				chance_counter += DIR_CHANCES[new_dirs_n];
				new_dirs_n++;
			}

			//	SCEGLI DIREZIONI IN CUI GENERARE
			for(int d = 0; d < DIRECTIONS_N; d++) new_dirs[d] = false;
			for(int i = 0; i < new_dirs_n; i++) {
				int r = rand() % (new_dirs_n - i);
				int d = 0;
				while(r > 0 || used_dirs[d] || new_dirs[d]) {
					if(!used_dirs[d] && !new_dirs[d]) r--;
					d++;
				}
				new_dirs[d] = true;
			}

			// PRIMA GENERA MURI E CASELLE ADIACENTI,
			for(int d = 0; d < DIRECTIONS_N; d++) {
				Coordinate nxt = Coordinate (s, DIRECTIONS[d]);
				if(nxt.inBounds(COORDINATE_ZERO, size_t)) {
					if(new_dirs[d]) map->physical[nxt.single()] = FLOOR_INSTANCE;
					else if(!used_dirs[d] && map->physical[nxt.single()] == NULL) map->physical[nxt.single()] = WALL_INSTANCE;
				}
			}
			//POI VA IN RICORSIONE SULLE DIREZIONI
			for(int d = 0; d < DIRECTIONS_N; d++) {
				if(new_dirs[d]) {
					Coordinate nxt = Coordinate(s, DIRECTIONS[d]);
					sets->makeSet(nxt.single());
					sets->merge(s.single(), nxt.single());
					generatePath(nxt, sets);
				}
			}
		}
	}

	int Room::getAdjacentWalls(Coordinate out[], UnionFind sets, s_coord currentParent) {
		int walls = 0;
		s_coord square = currentParent;
		do {
			for(int d = 0; d < DIRECTIONS_N; d++) {
				Coordinate nxt = Coordinate(Coordinate(square, size), DIRECTIONS[d]);
				if(nxt.inBounds(COORDINATE_ZERO, size_t)) {
					if(map->physical[nxt.single_set(size)]->getId() == ID_WALL) {
						out[walls] = nxt;
						walls++;
					}
				}
			}
			square = sets.next(square);
		} while(square != currentParent);
		return walls;
	}
	int Room::getBorderWalls(Coordinate walls[], int directions[], int walls_n, UnionFind sets, s_coord parent, int distance) {
		int border_n = 0;
		for(int i = 0; i < walls_n; i++)
		{
			int rand_d = rand() % DIRECTIONS_N, d = 0;		//inizio a controllare da una direzione casuale per avere più casualità
			bool found = false;
			while(!found && d < DIRECTIONS_N) {
				Coordinate dir = DIRECTIONS[rand_d];									//direzione in cui si prova a "rompere" il muro per connettere
				Coordinate nxt = Coordinate(walls[i], dir.times(distance, distance));	//casella da controllare dopo aver rotto il muro

				if(nxt.inBounds(COORDINATE_ZERO, size_t) && map->physical[nxt.single_set(size)]->getId() == ID_FLOOR && sets.find(nxt.single_set(size)) != parent) {
					walls[border_n] = walls[i];
					directions[border_n] = rand_d;
					border_n++;
					found = true;
				} else {
					d++;
					rand_d = (rand_d + 1) % DIRECTIONS_N;
				}
			}
		}
		return border_n;
	}
#pragma endregion GENERATION
#pragma endregion AUSILIARE


#pragma region SET_GET
//// GET
	Coordinate Room::getPos() {
		return pos;
	}
	Coordinate Room::getSize() {
		return size;
	}
	pRoom Room::getRoomInPosition(Coordinate pos) {
		return NULL;
	}
	/*void Room::getMap(pPhysical map[], Coordinate &size) {
		for(s_coord i = 0; i < this->map->getSize().x / scale_x * this->map->getSize().y; i++) map[i] = this->map->checkPosition(Coordinate(i * scale_x, this->map->getSize()));
		size = this->map->getSize().times(1. / scale_x, 1);
	}*/
	void Room::makeConnection(pRoom room, int dir, lock_type lt, bool first) {
		if(room != NULL && first) {
			int dir2 = (dir + 2) % DIRECTIONS_N;
			room->makeConnection(this, dir2, lt, false);
		}
	}
	bool Room::setPosition_strong(pPhysical obj, Coordinate pos) {
		Coordinate pos_end = Coordinate(pos, obj->getSize());	//vertice del rettangolo opposto a pos
		pPhysical physical[ROOM_AREA];
		int found = MapHandler::checkRectangle(map, physical, pos, pos_end);
		bool valid = false;
		int i = 0;
		while(valid && i < found) {
			if(physical[i]->isInanimate() || physical[i]->getId() == ID_CHEST) valid = false;
			else physical[i]->destroy(map);	//distruggi oggetto se è character o projectile
			i++;
		}
		return valid;
	}
#pragma endregion SET_GET



	/*void Room::debug() {
		WINDOW *w = newwin(ROOM_HEIGHT, ROOM_WIDTH, 0, 0);
		Coordinate i = Coordinate(0, 0, size);
		do {
			wmove(w,size.y-1-i.y,i.x);
			if(map->physical[i.single()] == NULL) waddch(w,'N');
			else if(map->physical[i.single()]->getId() == ID_WALL) waddch(w,'x');
			else if(map->physical[i.single()]->getId() == ID_FLOOR) waddch(w,'.');
			else if(map->physical[i.single()]->getId() == ID_DOOR) waddch(w,'D');
			else waddch(w,'5');
		//wgetch(w);
			i.next();
		} while(!i.equals(COORDINATE_ZERO));
		wgetch(w);
	}
	void Room::debug2() {
		WINDOW *w = newwin(ROOM_HEIGHT, ROOM_WIDTH, 0, 0);
		Coordinate i = Coordinate(COORDINATE_ZERO, size,COORDINATE_ZERO,size_t);
		do {
			wmove(w,size.y-1-i.y,i.x);
			if(map->physical[i.single()] == NULL) waddch(w,'N');
			else if(map->physical[i.single()]->getId() == ID_WALL) waddch(w,'x');
			else if(map->physical[i.single()]->getId() == ID_FLOOR) waddch(w,'.');
			else if(map->physical[i.single()]->getId() == ID_DOOR) waddch(w,'D');
			else waddch(w,'5');
		//wgetch(w);
			i.next();
		} while(!i.equals(COORDINATE_ZERO));
		wgetch(w);
	}*/