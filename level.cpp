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
		PriorityQueueRoom available(-1);
		//stanze generate
		pConnectedRoom rooms[N_ROOMS];
		for(int i = 1; i < N_ROOMS; i++) rooms[i] = NULL;
		rooms[0] = new ConnectedRoom(Coordinate(0, 0));
		this->curRoom = rooms[0];
		map[curRoom->getPos().single()] = curRoom;
		//aggiungi ad available le posizioni adiacenti alla prima stanza
		int r = rand() % DIRECTIONS_N;
		for(int i = 0; i < DIRECTIONS_N; i++) available.insert(RoomPosition(DIRECTIONS[(r+i)%4], 1));

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
			r = rand() % DIRECTIONS_N;
			for(int j = 0; j < DIRECTIONS_N; j++)
			{
				int dir = (r+j) % DIRECTIONS_N;															//direzione corrente (indice)
				RoomPosition nxt = RoomPosition(Coordinate(DIRECTIONS[dir], new_pos.getPos()), 1);	//posizione da controllare
				pConnectedRoom adjacent_room = findRoomAtCoordinates(rooms, 1, nxt.getPos());
				int adjacent_cell = available.find(nxt);
				
				if(adjacent_room != NULL) rooms[room]->makeConnection(adjacent_room, dir, randLockedDoor(*rooms[room], *adjacent_room));	//se è una stanza, collegala a quella appena generata
				else if(adjacent_cell != -1) available.increaseKey(nxt, RoomPosition(Coordinate(), 1));										//se era già presente come cella disponibile, aumentane il numero di stanze adiacenti
				else available.insert(nxt);																									//altrimenti aggiungi la cella come disponibile
			}
		}
		//avvia generazione di tutte le stanze
		for(int i = 0; i < N_ROOMS; i++) {
			if(rooms[i] != NULL) {
				rooms[i]->generate();
				spawnInRoom(rooms[i]);
			}
		}

		available.destroy();
	}
	void Level::spawnInRoom(pConnectedRoom room) {
		for(int i = 0; i < ENEMIES_N[level]; i++) curRoom->spawnEnemy(randEnemy());
		int chests_n = chestsNumber();
		for(int i = 0; i < chests_n; i++) curRoom->spawnChest(randChest());
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
					mvwaddch(levelWindow, y, x, cellValue);
					screen[y][x] = cellValue;
				}
			}
		}
	}

	void Level::update(int input) {
		curRoom->update(input);
		changeRoom();
	}

	void Level::changeRoom() {
		pDoor new_door = player->usedDoor();
		if(new_door != NULL) {
			curRoom->setPosition_strong(player, new_door->getEntrancePosition());	//riposiziona player (la funzione ha sempre successo perché si fa in modo che item e wall non spawnino vicino la porta)
			curRoom = curRoom->getRoomInPosition(new_door->getPosition());
			player->useDoor();
		}
	}
	void Level::nextLevel() {
		curRoom->recursiveDestroy();
		generateMap();
		level++;
	}

#pragma region SET_GET
	/*void Level::getLevelMap(pRoom map[]) {
		for(int i = 0; i < LEVEL_AREA; i++) map[i] = this->map[i];
	}*/
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
				if(position.inBounds(Coordinate(pivot->getPosition(), offset_max.negative()), Coordinate(pivot->getPosition(), offset_max)))	//se camera nel rettangolo con dimensioni offset_max e centro pivot
					pivotChanged = false;
				else {
					ratio /= change_pivot_speed;
					position = Coordinate(position, pivotDistance.times(ratio, ratio));
				}
			}
			//se il pivot non si è mosso
			else if(pivot->lastFrameMovement().equals(Coordinate(0, 0))) {
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

	pEnemy Level::randEnemy() {
		int r = rand() % ENEMIES_CHANCE_TOT[level];
		int i = 0;
		while(r >= ENEMIES_CHANCHES[level][i]) i++;
		pEnemy res = new Enemy();
		res = new Enemy();
		res->copyEnemy(ENEMIES_INSTANCES[level][i]);
		return res;
	}
	pChest Level::randChest() {
		int r = rand() % N_ITEMS;
		pChest res;
		if(r < N_ARTIFACTS) {
			pArtifact item = new Artifact();
			item->copyArtifact(ARTIFACT_INSTANCES[r]);
			res = new Chest(item);
		} else if(r < N_ARTIFACTS + N_ITEM_DIFENSIVO) {
			pItem_def item = new item_difensivo();
			item->copyItemDifensivo(ITEM_DIFENSIVO_INSTANCES[r - N_ARTIFACTS]);
			res = new Chest(item);
		} else {
			pWeapon item = new Weapon();
			item->copyWeapon(WEAPON_INSTANCES[r - (N_ARTIFACTS + N_ITEM_DIFENSIVO)]);
			res = new Chest(item);
		}
		return res;
	}
	int Level::chestsNumber() {
		return rand() % (CHESTS_N_MAX[level] - CHESTS_N_MIN[level]) + CHESTS_N_MIN[level];
	}
	
#pragma endregion AUSILIARIE