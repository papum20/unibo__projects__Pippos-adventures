#include "room.hpp"


#pragma region MAIN
	Room::Room(Coordinate pos) {
		//inzializza stanza
		this->pos = pos;
		scale_x = SCALE_X;
		size = Coordinate(ROOM_WIDTH, ROOM_HEIGHT);

		floorInstance = new Floor();
		wallInstance = new Wall();

		for(int i = 0; i < size.x * size.y; i++) map[i] = NULL;
	}
	void Room::recursiveDestroy() {
		Coordinate i(0, 0, size);
		do {
			map[i.single()]->destroy();
			i.next();
		} while(!i.equals(Coordinate(0, 0)));
		wallInstance->destroy();
		floorInstance->destroy();
		delete this;
	}

	void Room::update(char input) {
		Coordinate i(0, 0, size);
		do {
			int points = 0;
			map[i.single()]->update(map, input);
			i.next();
		} while(!i.equals(Coordinate(0, 0)));
	}

	/*pCharacter check_enemy_ranged (Projectile p){
		Coordinate start;
		Coordinate end;
		switch (p.direction){
			case 'u':
				start=new Coordinate ((p.pos).x, (p.pos).y-p.up_height);
				end =new Coordinate ((p.pos).x+p.up_width-1, (p.pos).y-p.up_height);
			case 'd':
				start=new Coordinate ((p.pos).x, (p.pos).y+1);
				end =new Coordinate ((p.pos).x+p.down_width-1, (p.pos).y+1);
			case 'r':
				start=new Coordinate ((p.pos).x+p.right_width, (p.pos).y-p.right_height+1);
				end =new Coordinate ((p.pos).x+p.right_width, (p.pos).y);
			case 'l':                           
				start=new Coordinate ((p.pos).x-1, (p.pos).y-p.left_height+1);
				end =new Coordinate ((p.pos).x-1, (p.pos).y);
			default:
				break;    
		}
		return (checkLine(start, end));
	}*/

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
			Coordinate start(rand() % av_size, size);
			Coordinate end(size, enemy->getSize());
			Coordinate i(start.x, start.y, start.x, start.y, end.x, end.y);
			do {
				map[i.single()] = enemy;
				i.next();
			} while(!i.equals(start));
		}
	}

	void Room::draw(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_size, Coordinate center) {
		//disegna dall'alto al basso, da sinistra a destra, così si mantiene la prospettiva quando un oggetto che si trova davanti ad un altro gli viene disegnato davanti
		Coordinate wstart = Coordinate(center.x - win_size.x / 2, center.y - win_size.y / 2), wend = Coordinate(center.x + ceil(win_size.x / 2.), center.y + ceil(win_size.y / 2.));
		Coordinate i = Coordinate(wstart.x, wstart.y, wstart.x, wstart.y, wend.x, wend.y);
		do {
			//wall e floor hanno una singola istanza e sono un caso a parte
			if(map[i.single()]->getId() == ID_WALL) map[i.single()]->drawAtPosition(scr, win_size, i);
			else {
				map[i.single()]->drawAtOwnPosition(scr, win_size);
				floorInstance->drawAtPosition(scr, win_size, i);
			}
			i.next();
		} while(!i.equals(wstart));
	}
#pragma endregion MAIN

#pragma region AUSILIARIE
#pragma region AUSILIARIE_PRINCIPALI
//// FUNZIONI AUSILIARIE PRINCIPALI
	void Room::generateSidesWalls() {
		for(int y = 0; y < size.y; y++) {
			int delta_x = 1;
			if(y != 0 && y != size.y - 1) delta_x = ROOM_WIDTH_T - 1;
			for(int x = 0; x < ROOM_WIDTH_T; x += delta_x) map[Coordinate(x, y).single()] = wallInstance;
		}
	}
	void Room::generateInnerRoom() {
		Coordinate rstart((ROOM_WIDTH_T - CENTRAL_ROOM_SIZE) / 2, (ROOM_HEIGHT - CENTRAL_ROOM_SIZE) / 2), rend((ROOM_HEIGHT + CENTRAL_ROOM_SIZE) / 2., (ROOM_WIDTH_T + CENTRAL_ROOM_SIZE) / 2);
		Coordinate i(rstart.x, rstart.y, rstart.x, rstart.y, rend.x, rend.y);
		do {
			map[i.single()] = floorInstance;
			i.next();
		} while(!i.equals(rstart));
	}
	void Room::generateAllPaths(pUnionFind sets) {
		Coordinate rand_p = Coordinate();
		rand_p.setMatrix(size);
		rand_p.randomize(0, size.x, 0, size.y);
		for(int i = 0; i < size.y * size.x; i++) {
			rand_p.next();
			if(map[rand_p.single()] == NULL) {
				sets->makeSet(rand_p.single());
				generatePath(rand_p, sets);
			}
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
						Coordinate tw = Coordinate(bw, dir.getTimes(dist, dist));
						map[tw.single()] = floorInstance;
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
		for(int y = 0; y < ROOM_HEIGHT; y++) {
			for(int x = ROOM_WIDTH_T - 1; x >= 0; x++) {
				for(int s = 0; s < SCALE_X; s++)
					map[Coordinate(x * scale_x + s, y).single()] = map[Coordinate(x, y).single()];
			}
		}
	}
#pragma endregion AUSILIARIE_PRINCIPALI

#pragma region AUSILIARIE_SECONDARIE
//// FUNZIONI AUSILIARIE SECONDARIE (USATE DALLE PRINCIPALI)
	void Room::generatePath(Coordinate s, pUnionFind sets)
	{
		if(!s.inOwnBounds()) return;
		else {
			map[s.single()] = floorInstance;

			bool used_dirs[DIR_TOT];	//direzioni usate
			int used_dirs_n;
			bool new_dirs[DIR_TOT];		//nuove direzioni da generare
			int new_dirs_n;

			// CONTA DIREZIONI INUTILIZZABILI (PERCHÈ GIÀ USATE O FUORI DALLA MAPPA)
			int tot_chance = DIR_CHANCES[0];	//somma delle probabilità delle direzioni disponibili
			int unused_dirs_n = 0;
			for(int d = 0; d < DIR_TOT; d++) {
				Coordinate nxt = Coordinate(s, DIRECTIONS[d]);
				if(map[nxt.single()] == NULL) {
					if(nxt.inOwnBounds()) {
						used_dirs[d] = false;
						unused_dirs_n++;
						tot_chance += DIR_CHANCES[unused_dirs_n];
					}
				}
				else {
					//se incontra altro pavimento (proveniente da un'altra generazione) li unisce
					if(map[nxt.single()]->getId() == ID_FLOOR)
						sets->merge(s.single(), nxt.single());
					used_dirs[d] = true;
				}
			}
			used_dirs_n = DIR_TOT - unused_dirs_n;

			if(used_dirs_n != DIR_TOT) {
				// SCEGLI NUMERO DI DIREZIONI DA GENERARE (TRA QUELLE DISPONIBILI)
				new_dirs_n = 0;
				int new_dirs_r = rand() % tot_chance;	//indice per generare un numero random di nuove direzioni
				int chance_counter = 0;
				while(new_dirs_r >= chance_counter + DIR_CHANCES[new_dirs_n]) {
					chance_counter += DIR_CHANCES[new_dirs_n];
					new_dirs_n++;
				}

				//	SCEGLI DIREZIONI IN CUI GENERARE
				for(int d = 0; d < DIR_TOT; d++) new_dirs[d] = false;
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
				for(int d = 0; d < DIR_TOT; d++) {
					if(new_dirs[d]) map[Coordinate(s, DIRECTIONS[d]).single()] = floorInstance;
					else if(!used_dirs[d]) map[Coordinate(s, DIRECTIONS[d]).single()] = wallInstance;
				}
				//POI VA IN RICORSIONE SULLE DIREZIONI
				for(int d = 0; d < DIR_TOT; d++) {
					if(new_dirs[d]) {
						Coordinate nxt = Coordinate(s, DIRECTIONS[d]);
						sets->makeSet(nxt.single());
						sets->merge(s.single(), nxt.single());
						generatePath(nxt, sets);
					}
				}
			}
		}
	}

	int Room::getAdjacentWalls(Coordinate out[], s_coord currentSet) {
		int walls = 0;
		s_coord square = currentSet;
		do {
			for(int d = 0; d < DIR_TOT; d++) {
				Coordinate p = Coordinate(square, size);
				Coordinate nxt = Coordinate(p, DIRECTIONS[d]);
				if(nxt.inOwnBounds() && map[nxt.single()]->getId() == ID_WALL) {
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
			int rand_d = rand() % DIR_TOT, d = 0;
			bool found = false;
			while(!found && d < DIR_TOT) {
				rand_d = (rand_d + 1) % DIR_TOT;
				Coordinate dir = DIRECTIONS[rand_d];
				Coordinate nxt = Coordinate(walls[i], dir.getTimes(distance, distance));
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

	bool Room::isSpawnAllowed(s_coord pos, Coordinate size) {
		Coordinate i(pos, size);
		bool isObstacle = false;
		do {
			if(!map[i.single()]->getId() == ID_FLOOR) isObstacle = true;
			else i.next();
		} while(!isObstacle && !i.single() != pos);
		return !isObstacle;
	}
	int Room::getFreeCells(s_coord available[], Coordinate size) {
		int length = 0;
		for(s_coord i = 0; i < size.x * size.y; i++) {
			if(isSpawnAllowed(i, size)) {
				available[length] = i;
				length++;
			}
		}
		return length;
	}
#pragma endregion AUSILIARIE_SECONDARIE

#pragma endregion AUSILIARE

#pragma region SET_GET
//// GET
	Coordinate Room::getPos() {
		return pos;
	}
	Coordinate Room::getSize() {
		return size;
	}
	void Room::getMap(pPhysical map[], Coordinate &size) {
		for(s_coord i = 0; i < size.x / scale_x * size.y; i++) map[i] = this->map[i * scale_x];
		size = this->size.getTimes(1. / scale_x, 1);
	}
	void Room::makeConnection(pRoom room, int dir, lock_type lt, bool first = true) {
		if(room != NULL && first) {
			int dir2 = (dir + 2) % DIR_TOT;
			room->makeConnection(this, dir2, lt, false);
		}
	}
#pragma endregion SET_GET