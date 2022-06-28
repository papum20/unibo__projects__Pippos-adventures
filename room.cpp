#include "room.hpp"



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
		//inizializza porte/stanze collegate
		n_doors_max = MAX_CONNECTED_R;
		for(int i = 0; i < n_doors_max; i++) doors[i] = NULL;
	}

	void Room::generate()
	{
		pUnionFind sets = new UnionFind();

		// GENERA MURI LATERALI
		for(int y = 0; y < height; y++) {
			int delta_x = 1;
			if(y != 0 && y != height - 1) delta_x = ROOM_WIDTH_T - 1;
			for(int x = 0; x < ROOM_WIDTH_T; x += delta_x) grid[y][x] = wallInstance;
		}

		// GENERA PORTE
		for(int door = 0; door < n_doors_sides; door++) {
			int xDoor, yDoor;
			doors[door]->getPosition(xDoor, yDoor);
			grid[yDoor][xDoor] = doors[door];
			sets->makeSet(toSingleCoordinate(xDoor, yDoor));
		}

		//CREA STANZA NELLA STANZA (QUADRATO VUOTO)

		// RIEMPI LA STANZA DI MURI E CORRIDOI
		int rand_x = rand() % ROOM_WIDTH_T, rand_y = rand() % height;
		for(int y = 0; y < height; y++) {
			for(int x = 0; x < ROOM_WIDTH_T; x++) {
				int rx = (rand_x + x) % ROOM_WIDTH_T, ry = (rand_y + y) % height;
				if(grid[ry][rx] == NULL) {
					sets->makeSet(toSingleCoordinate(rx, ry));
					generatePath(rx, ry, sets);
				}
			}
		}

		// FAI IN MODO CHE OGNI PUNTO SIA RAGGIUNGIBILE DA OGNI ALTRO PUNTO
		connectPaths(sets);

		// RIDIMENSIONA LA STANZA, OVVERO ESEGUI UN ALLARGAMENTO DI "X_SCALE" VOLTE

	}



//// AUSILIARIE
	void Room::generatePath(int x, int y, pUnionFind sets)
	{
		if(!validCoordinates(x, y, 0, ROOM_WIDTH_T, 0, height)) return;
		else {
			grid[y][x] = floorInstance;

			bool used_dirs[DIR_SIZE];		//direzioni usate
			int used_dirs_n;
			bool new_dirs[DIR_SIZE];		//nuove direzioni da generare
			int new_dirs_n;

			// CONTA DIREZIONI INUTILIZZABILI (PERCHÈ GIÀ USATE O FUORI DALLA MAPPA)
			int tot_chance = DIR_CHANCES[0];	//somma delle probabilità delle direzioni disponibili
			int unused_dirs_n = 0;
			for(int d = 0; d < DIR_SIZE; d++) {
				int nx = x + DIRECTIONS[d].x, ny = y + DIRECTIONS[d].y;
				if(grid[ny][nx] == NULL) {
					if(validCoordinates(nx, ny, 0, ROOM_WIDTH_T, 0, height)) {
						used_dirs[d] = false;
						unused_dirs_n++;
						tot_chance += DIR_CHANCES[unused_dirs_n];
					}
				}
				else {
					//se incontra altro pavimento (proveniente da un'altra generazione) li unisce
					if(grid[ny][nx] == floorInstance)
						sets->merge(toSingleCoordinate(x, y), toSingleCoordinate(nx, ny));
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
					if(new_dirs[d]) grid[y + DIRECTIONS[d].y][x + DIRECTIONS[d].x] = floorInstance;
					else if(!used_dirs[d]) grid[y + DIRECTIONS[d].y][x + DIRECTIONS[d].x] = wallInstance;
				}
				//POI VA IN RICORSIONE SULLE DIREZIONI
				for(int d = 0; d < DIR_SIZE; d++) {
					if(new_dirs[d]) {
						int nx = x + DIRECTIONS[d].x, ny = y + DIRECTIONS[d].y;
						sets->merge(toSingleCoordinate(x, y), toSingleCoordinate(nx, ny));
						generatePath(nx, ny, sets);
					}
				}
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
			int adjacentWalls_n = getAdjacentWalls(adjacentWalls, currentSet), borderWalls_n = 0;

			//FINCHÉ NON HA CONNESSO QUALCOSA, CERCA SET CHE CONFININO A UNA DETERMINATA DISTANZA OPPURE AUMENTA LA DISTANZA
			while(!hasConnected) {
				//OTTIENI I MURI DI CONFINE TRA DUE SET DIVERSI
				borderWalls_n = getBorderWalls(borderWalls, adjacentWalls, adjacentWalls_n, *sets, currentSet, distance);

				//SE NE HA TROVATI: CONNETTI (ROMPI IL MURO/I MURI)
				if(borderWalls_n != 0) {
					//ROMPI UN MURO A CASO TRA QUELLI TROVATI
					int r = rand() % borderWalls_n, brokenWall = 0;
					while(r > 0) {
						if(adjacentWalls[brokenWall].x != -1 && adjacentWalls[brokenWall].y != -1) r--;
						brokenWall++;
					}
					int bx = borderWalls[brokenWall].x, by = borderWalls[brokenWall].y;
					
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

/*					//ROMPI distance MURI A PARTIRE DA QUELLO, NELLA GIUSTA DIREZIONE
					for(int i = 0; i <= distance; i++) {
						int diff_x = bx - adjacentWalls[brokenWall].x, diff_y = by - adjacentWalls[brokenWall].y;
						int tx = bx + diff_x * i, ty = by + diff_y * i;
						grid[ty][tx] = floorInstance;
						sets->merge(currentSet, toSingleCoordinate(tx, ty));
					}*/
*/
					hasConnected = true;
				}
				//ALTRIMENTI CERCA A UNA DISTANZA MAGGIORE
				else
					distance++;
			}
		}
	}


// FUNZIONI AUSILIARIE SECONDARIE (USATE DALLE PRINCIPALI)
	int Room::getAdjacentWalls(Coordinate out[], s_coord currentSet) {
		int walls = 0;
		s_coord square = currentSet;
		do {
			for(int d = 0; d < DIR_SIZE; d++) {
				int x, y;
				toDoubleCoordinate(square, x, y);
				int nx = x + DIRECTIONS[d].x, ny = y + DIRECTIONS[d].y;
				if(validCoordinates(nx, ny, 0, ROOM_WIDTH_T, 0, ROOM_HEIGHT) && grid[ny][nx] == wallInstance) {
					out[walls] = {nx, ny};
					walls++;
				}
			}
		} while(square != currentSet);
		return walls;
	}
	int Room::getBorderWalls(Coordinate border[], Coordinate walls[], int walls_n, UnionFind sets, s_coord parent, int distance) {
		int border_n = 0;
		for(int i = 0; i < walls_n; i++) {
			int d = 0;
			bool found = false;
			while(!found && d < DIR_SIZE) {
				int nx = walls[i].x + DIRECTIONS[d].x * distance, ny = walls[i].y + DIRECTIONS[d].y * distance;
				if(validCoordinates(nx, ny, 0, ROOM_WIDTH_T, 0, ROOM_HEIGHT) && sets.find(toSingleCoordinate(nx, ny)) != parent) {
					border[i] = {nx, ny};
					border_n++;
					found = true;
				}
				else d++;
			}
			if(!found) border[i] = {-1, -1};
		}
		return border_n;
	}

//FUNZIONI AUSILIARIE GENERICHE (SEMPLICI E USATE SPESSO)	
	s_coord Room::toSingleCoordinate(int x, int y) {
		return y * width + x;
	}
	void Room::toDoubleCoordinate(s_coord xy, int &x, int &y) {
		y = xy / width;
		x = xy - y * width;
	}
	bool Room::validCoordinates(int x, int y, int xmin, int xmax, int ymin, int ymax) {
		return (x >= xmin && x < xmax && y >= ymin && y < ymax);
	}

//// SET
	void Room::makeConnection(pRoom room, int dir) {
		int dir2 = (dir+2) % DIR_SIZE;
		if(dir == 0) {			//su
			this->doors[dir] = new Door(this->width/2, 0, room);
			room->doors[dir2] = new Door(room->width/2, room->height-1, this);
		} else if(dir == 1) {	//destra
			this->doors[dir] = new Door(this->width-1, this->height/2, room);
			room->doors[dir2] = new Door(0, room->height/2, this);
		} else if(dir == 2) {	//giu
			this->doors[dir] = new Door(this->width/2, this->height-1, room);
			room->doors[dir2] = new Door(room->width/2, 0, this);
		} else if(dir == 3) {	//sinistra
			this->doors[dir] = new Door(0, this->height/2, room);
			room->doors[dir2] = new Door(room->width-1, room->height/2, this);
		}
	}
//// GET
	int Room::getX() {
		return x;
	}
	int Room::getY() {
		return y;
	}
	pRoom Room::getConnectedRoom(int dir) {
		if(dir < 0 || dir >= n_doors_max || doors[dir] == NULL) return NULL;
		else return doors[dir]->getConnected();
	}
/*	int Room::getSideDoors() {
		return n_doors_sides;
	}*/