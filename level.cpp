#include "level.hpp"

#pragma region MAIN
	Level::Level(int win_y, int win_x, int win_h, int win_w, pPlayer player) {
		width = CAMERA_WIDTH;
		height = CAMERA_HEIGHT;
		lr_border = LR_BORDER;
		tb_border = TB_BORDER;
		level = 0;

		//n_rooms = N_ROOMS;
		levelWindow = newwin(win_y, win_x, win_h, win_w);

		this->player = player;

		generateMap();

		//CAMERA
		setDefaultCameraSpecs();
		position = player->getPosition();
		lastMovement = Coordinate(0, 0);
		pivot = player;
		pivotChanged = true;
	}
	Level::Level(int win_y, int win_x, pPlayer player) {
		Level(win_y, win_x, CAMERA_HEIGHT, CAMERA_WIDTH, player);
	}

	void Level::generateMap()
	{
		for(int i = 0; i < ROOM_AREA; i++) map[i] = NULL;
		//posizioni disponibili (allo stesso tempo) per la generazione di una nuova stanza, quindi adiacenti a una già presente
		//implementato come min-heap; il terzo campo sono le stanze adiacenti, usate per confronto
		RoomPriorityQueue available(-1);
		//stanze generate
		pConnectedRoom rooms[N_ROOMS];
		for(int i = 1; i < N_ROOMS; i++) rooms[i] = NULL;
		rooms[0] = new ConnectedRoom(Coordinate(0, 0));
		this->curRoom = rooms[0];
		map[curRoom->getPos().single()] = curRoom;
		//aggiungi ad available le posizioni adiacenti alla prima stanza
		int r = rand() % DIR_TOT;
		for(int i = 0; i < DIR_TOT; i++) available.insert(RoomPosition(DIRECTIONS[(r+i)%4], 1));

		//genera le altre stanze
		for(int room = 1; room < N_ROOMS; room++)
		{
			//scegli la nuova posizione
			RoomPosition new_pos = available.unevenRandom();
			//crea la stanza
			rooms[room] = new ConnectedRoom(new_pos.getPos());
			available.remove(new_pos);
			map[new_pos.getPos().single()] = rooms[room];

			//aggiorna stanze adiacenti e celle disponibili
			r = rand() % DIR_TOT;
			for(int j = 0; j < DIR_TOT; j++)
			{
				int dir = (r+j) % DIR_TOT;															//direzione corrente (indice)
				RoomPosition nxt = RoomPosition(Coordinate(DIRECTIONS[dir], new_pos.getPos()), 1);	//posizione da controllare
				pConnectedRoom adjacent_room = findRoomAtCoordinates(rooms, 1, nxt.getPos());
				int adjacent_cell = available.find(nxt);
				
				if(adjacent_room != NULL) rooms[room]->makeConnection(adjacent_room, dir);					//se è una stanza, collegala a quella appena generata
				else if(adjacent_cell != -1) available.increaseKey(nxt, RoomPosition(Coordinate(), 1));		//se era già presente come cella disponibile, aumentane il numero di stanze adiacenti
				else available.insert(nxt);																	//altrimenti aggiungi la cella come disponibile
			}
		}
		//avvia generazione di tutte le stanze
		for(int i = 0; i < N_ROOMS; i++) {
			if(rooms[i] != NULL) {
				rooms[i]->generate();
				spawnInRoom(rooms[i]);
			}
		}
	}
	void Level::spawnInRoom(pConnectedRoom room) {
		for(int i = 0; i < ENEMIES_N[level]; i++)
			curRoom->spawnEnemy(randEnemy());
	}

	void Level::display() {
		cameraUpdate();
		displayAtPosition(position);
	}

	void Level::displayAtPosition(Coordinate center) {
		//inizializza array
		Cell t_scr[CAMERA_HEIGHT][CAMERA_WIDTH];	//matrice temporanea per il nuovo schermo da stampare
		//fai riempire l'array alla stanza corrente
		curRoom->draw(t_scr, Coordinate(width, height), center);

		//stampa e aggiorna array corrente
		for(int y = tb_border; y < height - tb_border; y++) {
			for(int x = lr_border; x < width - lr_border; x++) {
				chtype cellValue = t_scr[y][x].toChtype();
				if(screen[y][x] != cellValue) {
					mvwaddch(levelWindow, y, lr_border, cellValue);
					screen[y][x] = cellValue;
				}
			}
		}
	}

	void Level::update(char input) {
		curRoom->update(input);
		changeRoom();
		//controlla se il player è su una porta
		//pPhysical location = curRoom->checkPosition(player->getPosition());
		//if(location->getId() == ID_DOOR) curRoom->getDoorInPosition(location->getPosition())->setPlayerOn(true);
	}

	void Level::changeRoom() {
		/*pPhysical location = curRoom->checkPosition(player->getPosition());
		if(location->getId() == ID_DOOR) {
			pConnectedRoom next_room = curRoom->getRoomInPosition(player->getPosition());
			pDoor next_door = next_room->getDoorToRoom(curRoom);
			if(next_door->canUse()) {
				player->setPosition(next_door->getPosition());			//riposiziona player
				curRoom = next_room;
				next_door->setPlayerOn(true);
			}
		}*/
		pDoor new_door = player->usedDoor();
		if(new_door != NULL) {
				player->setPosition(new_door->getPosition());			//riposiziona player
				curRoom = new_door->getConnected();
		}
	}
	void Level::nextLevel() {
		curRoom->recursiveDestroy();
		generateMap();
		level++;
	}

#pragma region SET_GET
	void Level::getLevelMap(pRoom map[]) {
		for(int i = 0; i < LEVEL_AREA; i++) map[i] = this->map[i];
	}
	void Level::getRoomMap(pPhysical map[], Coordinate &size, pPlayer &player) {
		curRoom->getMap(map, size);
		player = this->player;

	}
	void Level::setPivot(pPhysical pivot) {
		pivotDistance = Coordinate(pivot->getPosition(), pivot->getPosition().negative());		//nuovo pivot - vecchio pivot
		pivot = pivot;
		pivotChanged = true;
	}
	void Level::setDefaultCameraSpecs() {
		offset_max = CAMERA_OFFSET_MAX;
		speed = CAMERA_SPEED;
		damping_speed = CAMERA_DAMPING_SPEED;
		damping_timeout = CAMERA_DAMPING_TIMEOUT;
		opposite_speed = CAMERA_OPPOSITE_SPEED;
		change_pivot_speed = CAMERA_CHANGE_PIVOT_SPEED;
		/*camera_offset_max_x = CAMERA_OFFSET_MAX_X;
		camera_offset_max_y = CAMERA_OFFSET_MAX_Y;
		camera_speed_x = CAMERA_SPEED_X;
		camera_speed_y = CAMERA_SPEED_Y;
		camera_damping_speed_x = CAMERA_DAMPING_SPEED_X;
		camera_damping_speed_y = CAMERA_DAMPING_SPEED_Y;
		camera_damping_time_x = CAMERA_DAMPING_TIME_X;
		camera_damping_time_y = CAMERA_DAMPING_TIME_Y;
		camera_opposite_speed_x = CAMERA_OPPOSITE_SPEED_X;
		camera_opposite_speed_y = CAMERA_OPPOSITE_SPEED_Y;
		camera_change_pivot_speed_x = CAMERA_CHANGE_PIVOT_SPEED_X;
		camera_change_pivot_speed_y = CAMERA_CHANGE_PIVOT_SPEED_Y;*/
		timer.set_max(CAMERA_DAMPING_TIMER, damping_timeout);
	}
#pragma endregion SET_GET

#pragma endregion MAIN


#pragma region AUSILIARIE
//// AUSILIARIE
	pConnectedRoom Level::findRoomAtCoordinates(pConnectedRoom rooms[], int len, Coordinate c) {
		int i = 0;
		pConnectedRoom res = NULL;
		while(res == NULL && i < len) {
			if(rooms[i]->getPos().equals(c)) res = rooms[i];
			else i++;
		}
		return res;
	}

	void Level::cameraUpdate() {
		if(width >= curRoom->getSize().x && height >= curRoom->getSize().y)
			position = Coordinate(width / 2, height / 2);
		
		else {
			Coordinate tolerance(REFRESH_RATE / damping_speed / PHYSICAL_MAX_SPEED, REFRESH_RATE / damping_speed / PHYSICAL_MAX_SPEED);
			float ratio = timer.deltaTime();
			//se il pivot è cambiato
			if(pivotChanged) {
				if(position.inBounds(Coordinate(pivot->getPosition(), offset_max.getNegative()), Coordinate(pivot->getPosition(), offset_max)))	//se camera nel rettangolo con dimensioni offset_max e centro pivot
					pivotChanged = false;
				else {
					ratio /= change_pivot_speed;
					position = Coordinate(position, pivotDistance.getTimes(ratio, ratio));
				}
			}
			//se il pivot non si è mosso
			else if(pivot->lastFrameMovement().equals(Coordinate(0, 0))) {
				if(Coordinate(position, pivot->getPosition().getNegative()).inBounds(tolerance.getNegative(), tolerance))	//se camera - pivot nel rettangolo di incertezza (di dimensioni piccole)
					position = pivot->getPosition();
				else if(!timer.is_active(CAMERA_DAMPING_TIMER))							//se si è appena fermato: avvia timer
					timer.start(CAMERA_DAMPING_TIMER);
				else if(timer.check(CAMERA_DAMPING_TIMER)) {						//se passato tempo di attesa: muoviti
					ratio /= damping_speed;
					position = Coordinate(position, (Coordinate(position, pivot->getPosition().getNegative())).getTimes(ratio, ratio));		//camera - (pivot - camera) * ratio = camera + (camera - pivot) * ratio
				}
			}
			//se si è mosso
			else {
				Coordinate target = Coordinate(pivot->getPosition(), pivot->getSpeed().getTimes(1 / PHYSICAL_MAX_SPEED, 1 / PHYSICAL_MAX_SPEED));	//pivot + pivot.speed / max_speed
				if(Coordinate(position, target.getNegative()).inBounds(tolerance.getNegative(), tolerance))		//se camera - target nel rettangolo di incertezza
					position = target;
				else {
					ratio /= speed;
					position = Coordinate(position, (Coordinate(target, position.getNegative())).getTimes(ratio, ratio));		//camera + (target - camera) * ratio
				}
			}

				//DEVE RIENTRARE NEL LIVELLO
				if(width >= curRoom->getSize().x) position.x = curRoom->getSize().x / 2;
				else if(cameraStart().x < 0) position.x = ceil(width / 2.) - 1;
				else if(cameraEnd().x >= curRoom->getSize().x) position.x = curRoom->getSize().x - 1 -  width / 2;

				if(height >= curRoom->getSize().y) position.y = curRoom->getSize().y / 2;
				else if(cameraStart().y < 0) position.y = ceil(height / 2.) - 1;
				else if(cameraEnd().y >= curRoom->getSize().y) position.y = curRoom->getSize().y - 1 - height / 2;
		}

	}

	Coordinate Level::cameraStart() {
		return Coordinate(position, Coordinate(ceil(curRoom->getSize().x / 2.) - 1, ceil(curRoom->getSize().y / 2.) - 1).getNegative());
	}
	Coordinate Level::cameraEnd() {
		return Coordinate(position, Coordinate(curRoom->getSize().x / 2, curRoom->getSize().y / 2));
	}

	pEnemy Level::randEnemy() {
		int r = rand() % ENEMIES_CHANCE_TOT[level];
		int i = 0;
		while(r >= ENEMIES_CHANCHES[level][i]) i++;
		pEnemy res = new Enemy();
		res = ENEMIES_INSTANCES[level][i];
		return res;
	}
	
#pragma endregion AUSILIARIE