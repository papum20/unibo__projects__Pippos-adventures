#include "level.hpp"


	Level::Level() {
		width = CAMERA_WIDTH;
		height = CAMERA_HEIGHT;

		//n_rooms = N_ROOMS;

		generateMap();
	}


	void Level::draw() {

	}


	void Level::generateMap()
	{
		//posizioni disponibili (allo stesso tempo) per la generazione di una nuova stanza, quindi adiacenti a una già presente
		//implementato come min-heap; il terzo campo sono le stanze adiacenti, usate per confronto
		int available[MAX_AVAILABLE][DIM_AVAILABLE];
		int n_available;		//spazi utilizzati
		//stanze generate
		pRoom rooms[N_ROOMS];
		for(int i = 1; i < N_ROOMS; i++) rooms[i] = NULL;
		rooms[0] = new Room(0, 0);
		this->curRoom = rooms[0];
		//aggiungi ad available le posizioni adiacenti alla prima stanza
		int r = rand() % DIR_SIZE;
		for(int i = 0; i < DIR_SIZE; i++) {
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
			rooms[room] = new Room(cx, cy);

			//aggiorna stanze adiacenti e celle disponibili
			bool first = true;
			r = rand() % DIR_SIZE;
			for(int j = 0; j < DIR_SIZE; j++)
			{
				int c_dir = (r+j) % DIR_SIZE;												//direzione corrente (indice)
				int nx = cx + DIRECTIONS[c_dir].x, ny = cy + DIRECTIONS[c_dir].y;			//x,y da controllare
				pRoom adjacent_room = findRoomAtCoordinates(rooms, room, nx, ny);
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
	}




//// AUSILIARIE
	pRoom Level::findRoomAtCoordinates(pRoom rooms[], int len, int x, int y) {
		int i = 0;
		pRoom res = NULL;
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