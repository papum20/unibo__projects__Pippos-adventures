#include "level.hpp"


#pragma region MAIN
	Level::Level(int win_x, int win_y, int win_w, int win_h, pPlayer player) : Overlay(win_x, win_y, win_w, win_h) {
		setUp(win_x, win_y, win_w, win_h, player);
	}
	Level::Level(int win_x, int win_y, pPlayer player, System_text *log) : Overlay(win_x, win_y, CAMERA_WIDTH, CAMERA_HEIGHT) {
		setUp(win_x, win_y, CAMERA_WIDTH, CAMERA_HEIGHT, player, log);
	}
	void Level::setUp(int win_x, int win_y, int win_w, int win_h, pPlayer player, System_text *log) {
		this->lr_border = LR_BORDER;
		this->tb_border = TB_BORDER;
		level = 0;
		this->player = player;
		this->log = log;

		map_size = Coordinate(N_ROOMS, N_ROOMS);
		generateMap();

		for(int y = 0; y < height; y++)
			for(int x = 0; x < width; x++) screen[y][x] = CHAR_EMPTY;
	}
	void Level::destroy() {
		destroyRooms();
		Overlay::destroy();
	}
	void Level::destroyRooms() {
		Coordinate i = Coordinate(0, 0, map_size);
		do {
			if(map[i.single()] != NULL) map[i.single()]->destroy();
			i.next();
		} while(!i.equals(COORDINATE_ZERO));
	}

	void Level::generateMap()
	{
		for(int i = 0; i < LEVEL_AREA; i++) map[i] = NULL;
		//posizioni disponibili (allo stesso tempo) per la generazione di una nuova stanza, quindi adiacenti a una già presente
		//implementato come min-heap; il terzo campo sono le stanze adiacenti, usate per confronto
		PriorityQueueRoom available = PriorityQueueRoom(-1);
		//stanze generate
		pConnectedRoom rooms[N_ROOMS];
		for(int i = 1; i < N_ROOMS; i++) rooms[i] = NULL;
		rooms[0] = new ConnectedRoom(LEVEL_CENTER);
		this->curRoom = rooms[0];
		map[curRoom->getPos().single_set(map_size)] = curRoom;
		//aggiungi ad available le posizioni adiacenti alla prima stanza
		int r = rand() % DIRECTIONS_N;
		for(int i = 0; i < DIRECTIONS_N; i++) {
			RoomPosition nxt = RoomPosition(Coordinate(curRoom->getPos(), DIRECTIONS[(r+i)%4]), 1);
			if(nxt.getPos().inBounds(COORDINATE_ZERO, map_size)) available.insert(nxt);
		}

		//genera le altre stanze
		for(int room = 1; room < N_ROOMS; room++)
		{
			//scegli la nuova posizione
			RoomPosition new_pos = available.unevenRandom();
			//crea la stanza
			if(room == N_ROOMS - 1) {								//se è l'ultima stanza: genera la stanza del boss
				while(new_pos.getConnected() == 4) {
					available.remove(new_pos);
					new_pos = available.unevenRandom();
				}
				rooms[room] = new BossRoom(new_pos.getPos());
			} else													//altrimenti genera una normale stanza con porte
				rooms[room] = new ConnectedRoom(new_pos.getPos());
			available.remove(new_pos);
			map[new_pos.getPos().single_set(map_size)] = rooms[room];

			//aggiorna stanze adiacenti e celle disponibili
			r = rand() % DIRECTIONS_N;
			for(int j = 0; j < DIRECTIONS_N; j++)
			{
				int dir = (r+j) % DIRECTIONS_N;										//direzione corrente (indice)
				Coordinate nxt_pos = Coordinate(new_pos.getPos(), DIRECTIONS[dir]);
				if(nxt_pos.inBounds(COORDINATE_ZERO, map_size)) {
					RoomPosition nxt = RoomPosition(nxt_pos, 1);					//posizione da controllare
					pConnectedRoom adjacent_room = findRoomAtCoordinates(rooms, room, nxt_pos);
					int adjacent_cell = available.findPos(nxt);
					
					if(adjacent_room != NULL) {
						if(adjacent_room->isBossRoom()) rooms[room]->makeConnection(adjacent_room, dir, LOCK_NONE);			//se è boss room, non mette porta bloccata
						else rooms[room]->makeConnection(adjacent_room, dir, randLockedDoor(*rooms[room], *adjacent_room));	//se è una stanza, collegala a quella appena generata
					}
					else if(adjacent_cell != -1) available.increaseKey(nxt, RoomPosition(Coordinate(), 1));										//se era già presente come cella disponibile, aumentane il numero di stanze adiacenti
					else available.insert(nxt);																									//altrimenti aggiungi la cella come disponibile
				}
			}
		}
		//avvia generazione di tutte le stanze
		for(int i = 0; i < N_ROOMS; i++) {
			rooms[i]->generate();
			if(i == 0) rooms[i]->spawn(level % LEVELS_N, player, true);
			else rooms[i]->spawn(level % LEVELS_N, player, false);
		}
		available.destroy();
	}

	void Level::display() {
		displayAtPosition(player->getPosition());
	}

	void Level::displayAtPosition(Coordinate center) {
		//inizializza array
		Cell t_scr[CAMERA_HEIGHT][CAMERA_WIDTH];	//matrice temporanea per il nuovo schermo da stampare
		//fai riempire l'array alla stanza corrente
		curRoom->draw(t_scr, Coordinate(width - lr_border * 2, height - tb_border * 2), center);

		//stampa e aggiorna array corrente
		//visto che room disegna dal basso mentre ncurses dall'alto, bisogna "rigirare" t_scr
		for(int room_y = 0; room_y < height - 2 * tb_border; room_y++) {
			for(int x = 0; x < width - 2 * lr_border; x++) {
				chtype cellValue = t_scr[room_y][x].toChtype();
				if(screen[room_y][x] != cellValue) {
					int scr_y = height - room_y - tb_border - 1;
					mvwaddch(window, scr_y, x + lr_border, cellValue);
					screen[room_y][x] = cellValue;
				}
			}
		}
		wrefresh(window);
	}
	void Level::open() {
		box(window, 0, 0);
		for(int y = 0; y < height; y++)
			for(int x = 0; x < width; x++) screen[y][x] = Cell().toChtype();
		log->open();
	}

	void Level::update(int input) {
		curRoom->update(input);
		changeRoom();
	}

	void Level::changeRoom() {
		pDoor new_door = player->usedDoor();
		if(new_door != NULL) {
			player->useDoor();
			if(new_door->isUseable()) {
				curRoom->remove(player);		//rimuovo player cosi che non faccia il delete se va in next level
				if(new_door->isBoss()) {
					nextLevel();
				} else {
					if(new_door->isLocked()) curRoom->unlockDoor(new_door);
					player->setPosition(curRoom->getEntrance(new_door));
					curRoom = curRoom->getConnectedRoom(new_door);
					curRoom->addCharacter_strong(player);				//riposiziona player (la funzione ha sempre successo perché si fa in modo che item e wall non spawnino vicino la porta)
				}
			}
		}
	}
	void Level::nextLevel() {
		destroyRooms();
		level++;
		generateMap();
	}

#pragma region SET_GET
	void Level::getLevelMap(pRoom map[LEVEL_AREA]) {
		for(int i = 0; i < LEVEL_AREA; i++) map[i] = this->map[i];
	}
	Coordinate Level::getSize() {
		return map_size;
	}
	int Level::getLevel() {
		return level;
	}
	pRoom Level::getCurrentRoom() {
		return curRoom;
	}
#pragma endregion SET_GET

#pragma endregion MAIN


#pragma region AUSILIARIE
//// AUSILIARIE
	lock_type Level::randLockedDoor(Room A, Room B) {
		return rand() % LOCK_TYPES_N;
	}
	pConnectedRoom Level::findRoomAtCoordinates(pConnectedRoom rooms[], int len, Coordinate c) {
		int i = 0;
		pConnectedRoom res = NULL;
		while(res == NULL && i < len) {
			if(rooms[i]->getPos().equals_int(c)) res = rooms[i];
			else i++;
		}
		return res;
	}
	
#pragma endregion AUSILIARIE
