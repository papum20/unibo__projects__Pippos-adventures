#include "room.hpp"


#pragma region MAIN
	Room::Room(int x, int y) {
		//inzializza stanza
		this->x = x;
		this->y = y;
		width = ROOM_WIDTH;
		height = ROOM_HEIGHT;

		floorInstance = new Floor();
		wallInstance = new Wall();

		for(int y = 0; y < height; y++)
			for(int x = 0; x < width; x++) grid[y][x] = NULL;
	}
	void Room::recursiveDestroy() {
		Coordinate i(0, 0, width, height);
		do {
			pPhysical t = grid[i.y][i.x];
			if(!t->isInanimate() && t->getId() != ID_DOOR) t->destroy();
			i.next();
		} while(!i.equals(Coordinate(0, 0)));
		wallInstance->destroy();
		floorInstance->destroy();
		delete this;
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

	void Room::draw(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_size, Coordinate center) {
		//disegna dall'alto al basso, da sinistra a destra, così si mantiene la prospettiva quando un oggetto che si trova davanti ad un altro gli viene disegnato davanti
		for(int y = center.y - win_size.y / 2; y < center.y + ceil(win_size.y / 2.); y++) {
			for(int x = center.x - win_size.x / 2; x < center.x + ceil(win_size.x / 2.); x++) {
				//wall e floor hanno una singola istanza e sono un caso a parte
				if(grid[y][x]->isInanimate()) grid[y][x]->drawAtPosition(scr, win_size, {y, x});
				else {
					grid[y][x]->drawAtOwnPosition(scr, win_size);
					floorInstance->drawAtPosition(scr, win_size, Coordinate(x, y));
				}
			}
		}
	}

	bool Room::moveObject(Physical ob, Coordinate move) {
		Coordinate newPos = Coordinate(ob.getPosition(), move);
		if(newPos.inOwnBounds() || grid[newPos.y][newPos.x]->getId() != ID_FLOOR || ob.isInanimate() || ob.getId() == ID_DOOR)
			return false;
		else {
			swapPositions(newPos, ob.getPosition());
			return true;
		}
	}
#pragma endregion MAIN

#pragma region AUSILIARIE
#pragma region AUSILIARIE_PRINCIPALI
//// FUNZIONI AUSILIARIE PRINCIPALI
	void Room::generateSidesWalls() {
		for(int y = 0; y < height; y++) {
			int delta_x = 1;
			if(y != 0 && y != height - 1) delta_x = ROOM_WIDTH_T - 1;
			for(int x = 0; x < ROOM_WIDTH_T; x += delta_x) grid[y][x] = wallInstance;
		}
	}
	void Room::generateInnerRoom() {
		for(int y = (ROOM_HEIGHT - CENTRAL_ROOM_SIZE) / 2; y < (ROOM_HEIGHT + CENTRAL_ROOM_SIZE) / 2; y++) {
			for(int x = (ROOM_WIDTH_T - CENTRAL_ROOM_SIZE) / 2; x < (ROOM_WIDTH_T + CENTRAL_ROOM_SIZE) / 2; x++)
				grid[y][x] = floorInstance;
		}
	}
	void Room::generateAllPaths(pUnionFind sets) {
		Coordinate rand_p = Coordinate();
		rand_p.setMatrix(width, height);
		rand_p.randomize(0, width, 0, height);
		for(int i = 0; i < height * width; i++) {
			rand_p.next();
			if(grid[rand_p.y][rand_p.x] == NULL) {
				sets->makeSet(rand_p.single());
				generatePath(rand_p, sets);
			}
		}
	}
	
	void Room::connectPaths(pUnionFind sets) {
		while(sets->getNumber() > 1) {
			bool hasConnected = false;
			int distance = 1;

			//TROVA I MURI ADIACENTI AL SET
			s_coord currentSet = sets->getNth(rand() % sets->getNumber());
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
					
					/*
					//CERCA LA GIUSTA DIREZIONE IN CUI ROMPERE
					int rand_dir = rand() % DIR_SIZE;
					int self_x, self_y;
					int adjacent_x, adjacent_y;
					do {
						int dx = DIRECTIONS[rand_dir].x, dy = DIRECTIONS[rand_dir].y;
						self_x = bx + dx, self_y = by + dy;
						adjacent_x = bx + dx * distance, adjacent_y = by + dy * distance;
						rand_dir = (rand_dir + 1) % DIR_SIZE;
					} while(!validCoordinates(self_x, self_y, 0, ROOM_WIDTH_T, 0, ROOM_HEIGHT) || 
							!validCoordinates(adjacent_x, adjacent_y, 0, ROOM_WIDTH_T, 0, ROOM_HEIGHT) || 
							sets->find(toSingleCoordinate(self_x, self_y)) != currentSet ||
							grid[adjacent_y][adjacent_x] == wallInstance || 
							sets->find(toSingleCoordinate(adjacent_x, adjacent_y)) == currentSet);					
					//non servono altri controlli perché si ha la certezza che il ciclo termini

					//ROMPI distance MURI A PARTIRE DA QUELLO, NELLA GIUSTA DIREZIONE
					for(int i = 0; i <= distance; i++) {
						int diff_x = bx - self_x, diff_y = by - self_y;
						int tx = bx + diff_x * i, ty = by + diff_y * i;
						grid[ty][tx] = floorInstance;
						sets->merge(currentSet, toSingleCoordinate(tx, ty));
					}*/

					//ROMPI distance MURI A PARTIRE DA QUELLO, NELLA GIUSTA DIREZIONE
					for(int dist = 0; dist <= distance; dist++) {
						Coordinate dir = DIRECTIONS[breakDirections[brokenWall]];
						Coordinate tw = Coordinate(bw, dir.getTimes(dist, dist));
						grid[tw.x][tw.x] = floorInstance;
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
			for(int x = ROOM_WIDTH_T; x >= 0; x++) {
				for(int s = 0; s < X_SCALE; s++)
					grid[y][x * X_SCALE + s] = grid[y][x];
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
			grid[s.y][s.x] = floorInstance;

			bool used_dirs[DIR_SIZE];		//direzioni usate
			int used_dirs_n;
			bool new_dirs[DIR_SIZE];		//nuove direzioni da generare
			int new_dirs_n;

			// CONTA DIREZIONI INUTILIZZABILI (PERCHÈ GIÀ USATE O FUORI DALLA MAPPA)
			int tot_chance = DIR_CHANCES[0];	//somma delle probabilità delle direzioni disponibili
			int unused_dirs_n = 0;
			for(int d = 0; d < DIR_SIZE; d++) {
				Coordinate nxt = Coordinate(s, DIRECTIONS[d]);
				if(grid[nxt.y][nxt.x] == NULL) {
					if(nxt.inOwnBounds()) {
						used_dirs[d] = false;
						unused_dirs_n++;
						tot_chance += DIR_CHANCES[unused_dirs_n];
					}
				}
				else {
					//se incontra altro pavimento (proveniente da un'altra generazione) li unisce
					if(grid[nxt.y][nxt.x]->getId() == ID_FLOOR)
						sets->merge(s.single(), nxt.single());
					used_dirs[d] = true;
				}
			}
			used_dirs_n = DIR_SIZE - unused_dirs_n;

			if(used_dirs_n != DIR_SIZE) {
				// SCEGLI NUMERO DI DIREZIONI DA GENERARE (TRA QUELLE DISPONIBILI)
				new_dirs_n = 0;
				int new_dirs_r = rand() % tot_chance;	//indice per generare un numero random di nuove direzioni
				int chance_counter = 0;
				while(new_dirs_r >= chance_counter + DIR_CHANCES[new_dirs_n]) {
					chance_counter += DIR_CHANCES[new_dirs_n];
					new_dirs_n++;
				}

				//	SCEGLI DIREZIONI IN CUI GENERARE
				for(int d = 0; d < DIR_SIZE; d++) new_dirs[d] = false;
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
				for(int d = 0; d < DIR_SIZE; d++) {
					if(new_dirs[d]) grid[s.y + DIRECTIONS[d].y][s.x + DIRECTIONS[d].x] = floorInstance;
					else if(!used_dirs[d]) grid[s.y + DIRECTIONS[d].y][s.x + DIRECTIONS[d].x] = wallInstance;
				}
				//POI VA IN RICORSIONE SULLE DIREZIONI
				for(int d = 0; d < DIR_SIZE; d++) {
					if(new_dirs[d]) {
						Coordinate nxt = Coordinate(s, DIRECTIONS[d]);
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
			for(int d = 0; d < DIR_SIZE; d++) {
				Coordinate p = Coordinate(square, width, height);
				Coordinate nxt = Coordinate(p, DIRECTIONS[d]);
				if(nxt.inOwnBounds() && grid[nxt.y][nxt.x]->getId() == ID_WALL) {
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
			int rand_d = rand() % DIR_SIZE, d = 0;
			bool found = false;
			while(!found && d < DIR_SIZE) {
				rand_d = (rand_d + 1) % DIR_SIZE;
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
#pragma endregion AUSILIARIE_SECONDARIE

#pragma region AUSILIARIE_GENERICHE
	void Room::swapPositions(Coordinate a, Coordinate b) {
		pPhysical tmp = grid[a.y][a.x];
		grid[a.y][a.x] = grid[b.y][b.x];
		grid[b.y][b.x] = tmp;
	}
#pragma endregion AUSILIARIE_GENERICHE

#pragma endregion AUSILIARE

#pragma region SET_GET
//// SET
	void Room::makeConnection(Room *room, int dir) {

	}
//// GET
	int Room::getX() {
		return x;
	}
	int Room::getY() {
		return y;
	}
	pRoom Room::getConnectedRoom(Coordinate pos) {
		return NULL;
	}
	pPhysical Room::checkPosition(Coordinate pos) {
		if(!pos.inBounds(Coordinate(0, 0), Coordinate(width, height)))
			return grid[pos.y][pos.x];
		else return NULL;
	}
#pragma endregion SET_GET