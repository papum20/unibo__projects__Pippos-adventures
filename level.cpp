#include "level.hpp"

#pragma region MAIN
	Level::Level(int win_y, int win_x, int win_h, int win_w, pPlayer player) {
		width = CAMERA_WIDTH;
		height = CAMERA_HEIGHT;
		lr_border = LR_BORDER;
		tb_border = TB_BORDER;

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
		//posizioni disponibili (allo stesso tempo) per la generazione di una nuova stanza, quindi adiacenti a una già presente
		//implementato come min-heap; il terzo campo sono le stanze adiacenti, usate per confronto
		int available[MAX_AVAILABLE][DIM_AVAILABLE];
		int n_available;		//spazi utilizzati
		//stanze generate
		pCRoom rooms[N_ROOMS];
		for(int i = 1; i < N_ROOMS; i++) rooms[i] = NULL;
		rooms[0] = new ConnectedRoom(0, 0);
		this->curRoom = rooms[0];
		//aggiungi ad available le posizioni adiacenti alla prima stanza
		int r = rand() % DIR_TOT;
		for(int i = 0; i < DIR_TOT; i++) {
			available[i][AV_X] = DIRECTIONS[(r+i)%4].x;
			available[i][AV_Y] = DIRECTIONS[(r+i)%4].y;
			available[i][AV_N] = 1;
		}
		n_available = 4;

		//genera le altre stanze
		for(int room = 1; room < N_ROOMS; room++)
		{
			//scegli la nuova posizione
			int randRoom = 0;
			int executions = MAX_RAND_EXEC;
			do {	//verrebbe comunque eseguito almeno una volta anche con il while
				if(rand() % GENERATION_CHANCE == 0) executions = 0;
				else {
					if(randRoom*2 + 1 < n_available && rand() % 2) randRoom = randRoom*2 + 1;
					else if(randRoom*2 + 2 < n_available) randRoom = randRoom*2 + 2;
					else {
						randRoom = 0;
						executions--;
					}
				}
			} while(executions > 0);
			//crea la stanza
			int cx = available[randRoom][AV_X], cy = available[randRoom][AV_Y];	//x,y correnti
			rooms[room] = new ConnectedRoom(cx, cy);

			//aggiorna stanze adiacenti e celle disponibili
			bool first = true;
			r = rand() % DIR_TOT;
			for(int j = 0; j < DIR_TOT; j++)
			{
				int c_dir = (r+j) % DIR_TOT;												//direzione corrente (indice)
				int nx = cx + DIRECTIONS[c_dir].x, ny = cy + DIRECTIONS[c_dir].y;			//x,y da controllare
				pCRoom adjacent_room = findRoomAtCoordinates(rooms, room, nx, ny);
				int adjacent_cell = findCellAtCoordinates(available, nx, ny);

				//se è una stanza, collegala a quella appena generata
				if(adjacent_room != NULL) rooms[room]->makeConnection(adjacent_room, c_dir);
				//se era già presente come cella disponibile, aumentane il numero di stanze adiacenti
				else if(adjacent_cell != -1) {
					available[adjacent_cell][AV_N]++;
					checkMinHeap(available, n_available, adjacent_cell);
				}
				//altrimenti aggiungi la cella come disponibile
				else {
					int ind;
					if(first) {
						ind = randRoom;
						first = false;
					}
					else {
						ind = n_available;
						n_available++;
					}

					available[ind][AV_X] = nx;
					available[ind][AV_Y] = ny;
					available[ind][AV_N] = 1;		//per la stanza appena generata
					checkMinHeap(available, n_available, ind);
				}
			}
			//se non è stata aggiunta alcuna cella, ridispone l'heap
			if(first) {
				available[randRoom][AV_X] = available[n_available-1][AV_X];
				available[randRoom][AV_Y] = available[n_available-1][AV_Y];
				available[randRoom][AV_N] = available[n_available-1][AV_N];
				n_available--;
				checkMinHeap(available, n_available, randRoom);
			}
		}
		//avvia generazione di tutte le stanze
		for(int i = 0; i < N_ROOMS; i++) {
			if(rooms[i] != NULL) rooms[i]->generate();
		}
	}

	void Level::display() {
		cameraUpdate();
		displayAtPosition(position);
	}

	void Level::displayAtPosition(Coordinate center) {
		//inizializza array
		Cell t_scr[CAMERA_HEIGHT][CAMERA_WIDTH];	//matrice temporanea per il nuovo schermo da stampare
		//fai riempire l'array alla stanza corrente
		curRoom->draw(t_scr, {width, height}, center);

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

	void Level::update() {
		changeRoom();
	}

	void Level::changeRoom() {
		pPhysical location = curRoom->checkPosition(player->getPosition());
		if(location->getId() == ID_DOOR) {
			curRoom = curRoom->getConnectedRoom(player->getPosition());
		
			//spawna cose da spawnare, riposiziona player
		}
	}
	void Level::nextLevel() {
		curRoom->recursiveDestroy();
		generateMap();
		//spawn
	}

#pragma region SET_GET
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
	pCRoom Level::findRoomAtCoordinates(pCRoom rooms[], int len, int x, int y) {
		int i = 0;
		pCRoom res = NULL;
		while(res == NULL && i < len) {
			if(rooms[i]->getX() == x && rooms[i]->getY() == y) res = rooms[i];
			else i++;
		}
		return res;
	}
	int Level::findCellAtCoordinates(int A[MAX_AVAILABLE][DIM_AVAILABLE], int x, int y) {
		int i = 0, res = -1;
		while(res == -1 && i < MAX_AVAILABLE) {
			if(A[i][AV_X] == x && A[i][AV_Y] == y)  res = i;
			else i++;
		}
		return res;
	}
	void Level::switchQueue(int A[MAX_AVAILABLE][DIM_AVAILABLE], int a, int b) {
		int tmp[DIM_AVAILABLE];
		for(int i = 0; i < DIM_AVAILABLE; i++) tmp[i] = A[a][i];
		for(int i = 0; i < DIM_AVAILABLE; i++) A[a][i] = A[b][i];
		for(int i = 0; i < DIM_AVAILABLE; i++) A[b][a] = tmp[i];
	}
	void Level::checkMinHeap(int H[MAX_AVAILABLE][DIM_AVAILABLE], int len, int i) {
		//controlla su
		int t = (i-1) / 2;
		while(i > 0 && H[i][AV_N] < H[t][AV_N]) {
			t = (i-1) / 2;
			switchQueue(H, i, t);
			i = t;
		}
		//controlla giu
		t = i*2 + 1;
		while((t < len && H[i][AV_N] > H[t][AV_N]) || (t+1 < len && H[i][AV_N] > H[t+1][AV_N])) {
			if(t+1 >= len || H[t][AV_N] < H[t+1][AV_N]) t = i*2 + 1;
			else t = i*2 + 2;
			switchQueue(H, i, t);
			i = t;
		}
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
					position.sum(pivotDistance.getTimes(ratio, ratio));
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
					position.sum((Coordinate(position, pivot->getPosition().getNegative())).getTimes(ratio, ratio));		//camera - (pivot - camera) * ratio = camera + (camera - pivot) * ratio
				}
			}
			//se si è mosso
			else {
				Coordinate target = Coordinate(pivot->getPosition(), pivot->getSpeed().getTimes(1 / PHYSICAL_MAX_SPEED, 1 / PHYSICAL_MAX_SPEED));	//pivot + pivot.speed / max_speed
				if(Coordinate(position, target.getNegative()).inBounds(tolerance.getNegative(), tolerance))		//se camera - target nel rettangolo di incertezza
					position = target;
				else {
					ratio /= speed;
					position.sum((Coordinate(target, position.getNegative())).getTimes(ratio, ratio));		//camera + (target - camera) * ratio
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
	
#pragma endregion AUSILIARIE