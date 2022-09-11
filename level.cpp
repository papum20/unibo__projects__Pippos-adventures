#include "level.hpp"


#pragma region MAIN
	Level::Level(int win_x, int win_y, int win_w, int win_h, pPlayer player) : Overlay(win_x, win_y, win_w, win_h) {
		setUp(win_x, win_y, win_w, win_h, player);
	}
	Level::Level(int win_x, int win_y, pPlayer player) : Overlay(win_x, win_y, CAMERA_WIDTH, CAMERA_HEIGHT) {
		setUp(win_x, win_y, CAMERA_WIDTH, CAMERA_HEIGHT, player);
	}
	void Level::setUp(int win_x, int win_y, int win_w, int win_h, pPlayer player) {
		this->lr_border = LR_BORDER;
		this->tb_border = TB_BORDER;
		level = 0;
		this->player = player;

		map_size = Coordinate(N_ROOMS, N_ROOMS);
		generateMap();

		//CAMERA
		setDefaultCameraSpecs();
		position = player->getPosition();
		lastMovement = Coordinate(0, 0);
		pivot = player;
		pivotChanged = true;

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
		rooms[0] = new BossRoom(LEVEL_CENTER);
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
			if(i == 0) rooms[i]->spawn(level, player, true);
			else rooms[i]->spawn(level, player, false);
		}
		available.destroy();
	}

	void Level::display() {
		//cameraUpdate();
		//displayAtPosition(position);
		//displayAtPosition(Coordinate(CENTRAL_ROOM_WIDTH_T*SCALE_X/2, CENTRAL_ROOM_HEIGHT/2));
		displayAtPosition(player->getPosition());
		//displayAtPosition(Coordinate(ROOM_WIDTH / 2, 0));
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
	pRoom Level::getCurrentRoom() {
		return curRoom;
	}
	/*void Level::getRoomMap(pPhysical map[], Coordinate &size, pPlayer &player) {
		curRoom->getMap(map, size);
		player = this->player;

	}*/
	void Level::setPivot(pPhysical pivot) {
		pivotDistance = Coordinate(pivot->getPosition(), this->pivot->getPosition().negative());		//nuovo pivot - vecchio pivot
		this->pivot = pivot;
		pivotChanged = true;
	}
	void Level::setDefaultCameraSpecs() {
		offset_max = CAMERA_OFFSET_MAX;
		speed = CAMERA_SPEED;
		damping_speed = CAMERA_DAMPING_SPEED;
		damping_timeout = CAMERA_DAMPING_TIMEOUT;
		opposite_speed = CAMERA_OPPOSITE_SPEED;
		change_pivot_speed = CAMERA_CHANGE_PIVOT_SPEED;
		timer.set_max(CAMERA_DAMPING_TIMER, damping_timeout);
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

	void Level::cameraUpdate() {
		if(width >= curRoom->getSize().x && height >= curRoom->getSize().y)
			position = curRoom->getSize().times(.5, .5);
		
		else {
			Coordinate tolerance = Coordinate(REFRESH_RATE / damping_speed / PHYSICAL_MAX_SPEED, REFRESH_RATE / damping_speed / PHYSICAL_MAX_SPEED);
			float ratio = timer.deltaTime();
			//se il pivot è cambiato
			if(pivotChanged) {
				if(position.inBounds(Coordinate(pivot->getPosition(), offset_max.negative()), Coordinate(pivot->getPosition(), offset_max)))	//se camera nel rettangolo con dimensioni offset_max e centro pivot
					pivotChanged = false;
				else {
					ratio /= change_pivot_speed;
					position = Coordinate(position, pivotDistance.times(ratio, ratio));
				}
			}
			//se il pivot non si è mosso
			else if(pivot->lastFrameMovement().equals(COORDINATE_ZERO)) {
				if(Coordinate(position, pivot->getPosition().negative()).inBounds(tolerance.negative(), tolerance))	//se camera - pivot nel rettangolo di incertezza (di dimensioni piccole)
					position = pivot->getPosition();
				else if(!timer.is_active(CAMERA_DAMPING_TIMER))							//se si è appena fermato: avvia timer
					timer.start(CAMERA_DAMPING_TIMER);
				else if(timer.check(CAMERA_DAMPING_TIMER)) {						//se passato tempo di attesa: muoviti
					ratio /= damping_speed;
					position = Coordinate(position, (Coordinate(position, pivot->getPosition().negative())).times(ratio, ratio));		//camera - (pivot - camera) * ratio = camera + (camera - pivot) * ratio
				}
			}
			//se si è mosso
			else {
				Coordinate target = Coordinate(pivot->getPosition(), pivot->getSpeed().times(1 / PHYSICAL_MAX_SPEED, 1 / PHYSICAL_MAX_SPEED));	//pivot + pivot.speed / max_speed
				if(Coordinate(position, target.negative()).inBounds(tolerance.negative(), tolerance))		//se camera - target nel rettangolo di incertezza
					position = target;
				else {
					ratio /= speed;
					position = Coordinate(position, (Coordinate(target, position.negative())).times(ratio, ratio));		//camera + (target - camera) * ratio
				}
			}

				//DEVE RIENTRARE NEL LIVELLO
				if(width >= curRoom->getSize().x) position.x = curRoom->getSize().x / 2;
				else if(cameraStart().x < 0) position.x = Math::ceil(width / 2.) - 1;
				else if(cameraEnd().x >= curRoom->getSize().x) position.x = curRoom->getSize().x - 1 -  width / 2;

				if(height >= curRoom->getSize().y) position.y = curRoom->getSize().y / 2;
				else if(cameraStart().y < 0) position.y = Math::ceil(height / 2.) - 1;
				else if(cameraEnd().y >= curRoom->getSize().y) position.y = curRoom->getSize().y - 1 - height / 2;
		}

	}

	Coordinate Level::cameraStart() {
		return Coordinate(position, Coordinate(Math::ceil(curRoom->getSize().x / 2.) - 1, Math::ceil(curRoom->getSize().y / 2.) - 1).negative());
	}
	Coordinate Level::cameraEnd() {
		return Coordinate(position, Coordinate(curRoom->getSize().x / 2, curRoom->getSize().y / 2));
	}
	
#pragma endregion AUSILIARIE