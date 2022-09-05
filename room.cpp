#include "room.hpp"


#pragma region MAIN
	Room::Room(Coordinate pos) {
		//inzializza stanza
		this->pos = pos;
		scale_x = SCALE_X;
		size_t = Coordinate(ROOM_WIDTH_T, ROOM_HEIGHT);
		size = size_t.times(scale_x, 1);

		map = new Map;
		map->size = size;
		//mappe
		for(int i = 0; i < size.x * size.y; i++) {
			map->physical[i] = NULL;
			map->characters[i] = NULL;
		}
	}
	void Room::recursiveDestroy() {
		Coordinate i(0, 0, size);
		do {
			pPhysical obj = map->physical[i.single()];
			if(obj != NULL && obj->getId() != ID_WALL && obj->getId() != ID_FLOOR) map->physical[i.single()]->destroy();
			i.next();
		} while(!i.equals(Coordinate(0, 0)));
		delete this;
	}
	void Room::update(int input) {
		Coordinate i(0, 0, size);
		do {
			int points = 0;
			map->characters[i.single()]->update(map);
			i.next();
		} while(!i.equals(Coordinate(0, 0)));
	}

	void Room::generate()
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
		Coordinate wstart = Coordinate(center.x - win_size.x / 2, center.y - win_size.y / 2), wend = Coordinate(center.x + Math::ceil(win_size.x / 2.), center.y + Math::ceil(win_size.y / 2.));
		Coordinate i = Coordinate(wstart, wstart, wend);
		do {
			Coordinate i_reverse = Coordinate(i.x, wstart.y + (wend.y - i.y));
			pPhysical obj = MapHandler::checkPosition(map, i_reverse);
			if(obj->isInanimate()) obj->drawAtPosition(scr, wstart, win_size, i_reverse);
			else {
				obj->drawAtOwnPosition(scr, wstart, win_size);
				FLOOR_INSTANCE->drawAtPosition(scr, wstart, win_size, i_reverse);
			}
			i.next();
		} while(!i.equals(wstart));
	}
#pragma endregion MAIN


#pragma region AUSILIARIE

	int Room::getFreeCells(s_coord available[], Coordinate size) {
		int length = 0;
		Coordinate i = Coordinate(Coordinate(0, 0), size);
		do {
			if(MapHandler::isFreeSpace(map, i, Coordinate(i, size))) {
				available[length] = i.single();
				length++;
			}
			i.next();
		} while(!i.equals(Coordinate(0, 0)));
		return length;
	}
//// ADD
	void Room::addCharacter(pCharacter character) {
		Coordinate i = Coordinate(character->getPosition(), character->getPosition(), Coordinate(character->getPosition(), character->getSize()));
		do {
			map->physical[i.single()] = character;
			map->characters[i.single()] = character;
		} while(!i.equals(character->getPosition()));
	}
	void Room::addChest(pChest chest) {
		Coordinate i = Coordinate(chest->getPosition(), chest->getPosition(), Coordinate(chest->getPosition(), chest->getSize()));
		do {
			map->physical[i.single()] = chest;
			map->chests[i.single()] = chest;
		} while(!i.equals(chest->getPosition()));
	}


#pragma region GENERATION
	void Room::generateSidesWalls() {
		for(int y = 0; y < size_t.y; y++) {
			int delta_x = 1;
			if(y != 0 && y != size_t.y - 1) delta_x = size_t.x - 1;
			else delta_x = 1;
			for(int x = 0; x < size_t.x; x += delta_x) map->physical[Coordinate(x, y, size).single()] = WALL_INSTANCE;
		}
	}
	void Room::generateInnerRoom() {
		Coordinate rstart((size_t.x - CENTRAL_ROOM_SIZE) / 2, (size_t.y - CENTRAL_ROOM_SIZE) / 2), rend((size_t.y + CENTRAL_ROOM_SIZE) / 2., (size_t.x + CENTRAL_ROOM_SIZE) / 2);
		Coordinate i(rstart, rstart, rend);
		do {
			map->physical[i.single()] = FLOOR_INSTANCE;
			i.next();
		} while(!i.equals(rstart));
	}
	void Room::generateAllPaths(pUnionFind sets) {
		Coordinate rand_p = Coordinate();
		rand_p.setMatrix(size_t);
		rand_p.randomize(0, size_t.x, 0, size_t.y);
		for(int i = 0; i < size_t.y * size_t.x; i++) {
			if(map->physical[rand_p.single()] == NULL) {
				sets->makeSet(rand_p.single());
				generatePath(rand_p, sets);
			}
			rand_p.next();
		}
	}
	void Room::connectPaths(pUnionFind sets) {
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
						map->physical[tw.single()] = FLOOR_INSTANCE;
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
	void Room::resizeMap() {
		for(int xy = size.x * size.y - 1; xy >= 0; xy--) {
			Coordinate xy_t = Coordinate(xy, size).times(1. / scale_x, 1);
			map->physical[xy] = map->physical[xy_t.single()];
		}
	}
	void Room::generatePath(Coordinate s, pUnionFind sets)
	{
		map->physical[s.single()] = FLOOR_INSTANCE;

		bool used_dirs[DIRECTIONS_N];	//direzioni usate
		int used_dirs_n;
		bool new_dirs[DIRECTIONS_N];	//nuove direzioni da generare
		int new_dirs_n;

		// CONTA DIREZIONI INUTILIZZABILI (PERCHÈ GIÀ USATE O FUORI DALLA MAPPA)
		int tot_chance = DIR_CHANCES[0];	//somma delle probabilità delle direzioni disponibili
		int unused_dirs_n = 0;
		for(int d = 0; d < DIRECTIONS_N; d++) {
			Coordinate nxt = Coordinate(s, DIRECTIONS[d]);
			if(map->physical[nxt.single()] == NULL) {
				if(nxt.inOwnBounds()) {
					used_dirs[d] = false;
					unused_dirs_n++;
					tot_chance += DIR_CHANCES[unused_dirs_n];
				}
			}
			else {
				//se incontra altro pavimento (proveniente da un'altra generazione) li unisce
				if(map->physical[nxt.single()]->getId() == ID_FLOOR)
					sets->merge(s.single(), nxt.single());
				used_dirs[d] = true;
			}
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
				if(new_dirs[d]) map->physical[Coordinate(s, DIRECTIONS[d]).single()] = FLOOR_INSTANCE;
				else if(!used_dirs[d]) map->physical[Coordinate(s, DIRECTIONS[d]).single()] = WALL_INSTANCE;
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

	int Room::getAdjacentWalls(Coordinate out[], s_coord currentSet) {
		int walls = 0;
		s_coord square = currentSet;
		do {
			for(int d = 0; d < DIRECTIONS_N; d++) {
				Coordinate p = Coordinate(square, size);
				Coordinate nxt = Coordinate(p, DIRECTIONS[d]);
				if(nxt.inOwnBounds() && map->physical[nxt.single()]->getId() == ID_WALL) {
					out[walls] = nxt;
					walls++;
				}
			}
		} while(square != currentSet);
		return walls;
	}
	int Room::getBorderWalls(Coordinate border[], int directions[], Coordinate walls[], int walls_n, UnionFind sets, s_coord parent, int distance) {
		int border_n = 0;
		for(int i = 0; i < walls_n; i++) {
			int rand_d = rand() % DIRECTIONS_N, d = 0;
			bool found = false;
			while(!found && d < DIRECTIONS_N) {
				rand_d = (rand_d + 1) % DIRECTIONS_N;
				Coordinate dir = DIRECTIONS[rand_d];
				Coordinate nxt = Coordinate(walls[i], dir.times(distance, distance));
				if(nxt.inOwnBounds() && sets.find(nxt.single()) != parent) {
					border[i] = {nxt.x, nxt.y};
					border_n++;
					directions[i] = rand_d;
					found = true;
				}
				else d++;
			}
			if(!found) border[i] = Coordinate(-1, -1);
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
			else physical[i]->destroy();	//distruggi oggetto se è character o projectile
			i++;
		}
		return valid;
	}
#pragma endregion SET_GET