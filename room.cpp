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
		int width_t = width / X_SCALE;
		pUnionFind sets = new UnionFind();

		// GENERA MURI LATERALI
		for(int y = 0; y < height; y++) {
			int delta_x = 1;
			if(y != 0 && y != height - 1) delta_x = width_t - 1;
			for(int x = 0; x < width_t; x += delta_x) grid[y][x] = wallInstance;
		}

		// GENERA PORTE
		for(int door = 0; door < n_doors_sides; door++) {
			int xDoor, yDoor;
			doors[door]->getPosition(xDoor, yDoor);
			grid[yDoor][xDoor] = doors[door];
			sets->makeSet(singleCoordinate(xDoor, yDoor));
		}

		//CREA STANZA NELLA STANZA (QUADRATO VUOTO)

		// RIEMPI LA STANZA DI MURI E CORRIDOI
		int rand_x = rand() % width_t, rand_y = rand() % height;
		for(int y = 0; y < height; y++) {
			for(int x = 0; x < width_t; x++) {
				int rx = (rand_x + x) % width_t, ry = (rand_y + y) % height;
				if(grid[ry][rx] == NULL) {
					sets->makeSet(singleCoordinate(rx, ry));
					generatePath(rx, ry, sets);
				}
			}
		}

		// FAI IN MODO CHE OGNI PUNTO SIA RAGGIUNGIBILE DA OGNI ALTRO PUNTO

		// RIDIMENSIONA LA STANZA, OVVERO ESEGUI UN ALLARGAMENTO DI "X_SCALE" VOLTE

	}



//// AUSILIARIE
	void Room::generatePath(int x, int y, pUnionFind sets)
	{
		int width_t = width / X_SCALE;
		if(!validCoordinates(x, y, 0, width_t, 0, height)) return;
		else if(grid[y][x] != NULL) return;
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
				int nx = x + DIRECTIONS[d][0], ny = y + DIRECTIONS[d][1];
				if(validCoordinates(nx, ny, 0, width_t, 0, height) && grid[ny][nx] == NULL) {
					used_dirs[d] = false;
					unused_dirs_n++;
					tot_chance += DIR_CHANCES[unused_dirs_n];
				}
				else used_dirs[d] = true;
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
					while(r > 0 || used_dirs[d] == true || new_dirs[d] == true) {
						if(used_dirs[d] == false && new_dirs[d] == false) r--;
						d++;
					}
					new_dirs[d] = true;
				}

				// PRIMA GENERA MURI, POI VA IN RICORSIONE SULLE DIREZIONI
				for(int d = 0; d < DIR_SIZE; d++)
					if(new_dirs[d] == false && used_dirs[d] == false) grid[y + DIRECTIONS[d][1]][x + DIRECTIONS[d][0]] = wallInstance;
				for(int d = 0; d < DIR_SIZE; d++) {
					if(new_dirs[d] == true) {
						int nx = x + DIRECTIONS[d][0], ny = y + DIRECTIONS[d][1];
						sets->merge(singleCoordinate(x, y), singleCoordinate(nx, ny));
						generatePath(nx, ny, sets);
					}
				}
			}
		}
	}
	/* OSS.:
		può succedere che anche se la funzione sceglie di generare in un determinato numero di direzioni,
		non vengano effettivamente usate tutte, perché magari una volta partita la ricorsione da una direzione,
		questa va a finire in un'altra uscente dallo stesso punto, ma andando a porci un muro.
	*/



	int Room::singleCoordinate(int x, int y) {
		return y * width + x;
	}
	void Room::doubleCoordinate(int xy, int &x, int &y) {
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