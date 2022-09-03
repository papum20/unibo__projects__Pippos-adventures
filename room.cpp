#include "room.hpp"


#pragma region MAIN
	Room::Room(Coordinate pos) {
		//inzializza stanza
		this->pos = pos;
		size = Coordinate(ROOM_WIDTH, ROOM_HEIGHT);
		scale_x = SCALE_X;

		map = new Map;
		map->size = size;
		//mappe
		for(int i = 0; i < size.x * size.y; i++) {
			map->physical[i] = NULL;
			map->characters[i] = NULL;
		}
	}
	void Room::recursiveDestroy() {
		Coordinate i(0, 0, size);
		do {
			map->physical[i.single()]->destroy();
			i.next();
		} while(!i.equals(Coordinate(0, 0)));
		delete this;
	}
	void Room::update(int input) {
		Coordinate i(0, 0, size);
		do {
			int points = 0;
			map->characters[i.single()]->update(map, input);
			i.next();
		} while(!i.equals(Coordinate(0, 0)));
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

	void Room::spawnEnemy(pEnemy enemy) {
		s_coord available[ROOM_AREA];
		int av_size = getFreeCells(available, enemy->getSize());
		if(av_size > 0) {
			enemy->setPosition(Coordinate(available[rand() % av_size], size));
			addCharacter(enemy);
		}
	}
	void Room::spawnChest(pChest chest) {
		s_coord available[ROOM_AREA];
		int av_size = getFreeCells(available, chest->getSize());
		if(av_size > 0) {
			chest->setPosition(Coordinate(available[rand() % av_size], size));
			addChest(chest);
		}
	}

	void Room::draw(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_size, Coordinate center) {
		//disegna dall'alto al basso, da sinistra a destra, così si mantiene la prospettiva quando un oggetto che si trova davanti ad un altro gli viene disegnato davanti
		Coordinate wstart = Coordinate(center.x - win_size.x / 2, center.y - win_size.y / 2), wend = Coordinate(center.x + Math::ceil(win_size.x / 2.), center.y + Math::ceil(win_size.y / 2.));
		Coordinate i = Coordinate(wstart, wstart, wend);
		do {
			pPhysical obj = MapHandler::checkPosition(map, i);
			if(obj->isInanimate()) obj->drawAtPosition(scr, win_size, i);
			else {
				obj->drawAtOwnPosition(scr, win_size);
				FLOOR_INSTANCE->drawAtPosition(scr, win_size, i);
			}
			i.next();
		} while(!i.equals(wstart));
	}
#pragma endregion MAIN


#pragma region AUSILIARIE
	int Room::getFreeCells(s_coord available[], Coordinate size) {
		int length = 0;
		Coordinate i = Coordinate(Coordinate(0, 0), size);
		do {
			if(isFreeSpace(i, Coordinate(i, size))) {
				available[length] = i.single();
				length++;
			}

		} while(!i.equals(Coordinate(0, 0)));
		return length;
	}
	bool Room::isFreeSpace(Coordinate start, Coordinate end) {
		Coordinate i = Coordinate(start, start, Coordinate(start, end));
		bool allowed = true;
		do {
			if(map->physical[i.single()]->getId() != ID_FLOOR) allowed = false;
			else i.next();
		} while(allowed && !i.equals(start));
		return allowed;
	}
//// ADD
	void Room::addCharacter(pCharacter character) {
		Coordinate i = Coordinate(character->getPosition(), character->getPosition(), Coordinate(character->getPosition(), character->getSize()));
		do {
			map->physical[i.single()] = character;
			map->characters[i.single()] = character;
		} while(!i.equals(character->getPosition()));
	}
	void Room::addChest(pChest chest) {
		Coordinate i = Coordinate(chest->getPosition(), chest->getPosition(), Coordinate(chest->getPosition(), chest->getSize()));
		do {
			map->physical[i.single()] = chest;
			map->chests[i.single()] = chest;
		} while(!i.equals(chest->getPosition()));
	}


#pragma region GENERATION
	void Room::generateSidesWalls() {
		for(int y = 0; y < size.y; y++) {
			int delta_x = 1;
			if(y != 0 && y != size.y - 1) delta_x = ROOM_WIDTH_T - 1;
			for(int x = 0; x < ROOM_WIDTH_T; x += delta_x) map->physical[Coordinate(x, y).single()] = WALL_INSTANCE;
		}
	}
	void Room::generateInnerRoom() {
		Coordinate rstart((ROOM_WIDTH_T - CENTRAL_ROOM_SIZE) / 2, (ROOM_HEIGHT - CENTRAL_ROOM_SIZE) / 2), rend((ROOM_HEIGHT + CENTRAL_ROOM_SIZE) / 2., (ROOM_WIDTH_T + CENTRAL_ROOM_SIZE) / 2);
		Coordinate i(rstart, rstart, rend);
		do {
			map->physical[i.single()] = FLOOR_INSTANCE;
			i.next();
		} while(!i.equals(rstart));
	}
	void Room::generateAllPaths(pUnionFind sets) {
		Coordinate rand_p = Coordinate();
		rand_p.setMatrix(size);
		rand_p.randomize(0, size.x, 0, size.y);
		for(int i = 0; i < size.y * size.x; i++) {
			rand_p.next();
			if(map->physical[rand_p.single()] == NULL) {
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
						Coordinate tw = Coordinate(bw, dir.times(dist, dist));
						map->physical[tw.single()] = FLOOR_INSTANCE;
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
					map->physical[Coordinate(x * scale_x + s, y).single()] = map->physical[Coordinate(x, y).single()];
			}
		}
	}
#pragma endregion GENERATION
#pragma endregion AUSILIARE


#pragma region SET_GET
//// GET
	Coordinate Room::getPos() {
		return pos;
	}
	Coordinate Room::getSize() {
		return size;
	}
	/*void Room::getMap(pPhysical map[], Coordinate &size) {
		for(s_coord i = 0; i < this->map->getSize().x / scale_x * this->map->getSize().y; i++) map[i] = this->map->checkPosition(Coordinate(i * scale_x, this->map->getSize()));
		size = this->map->getSize().times(1. / scale_x, 1);
	}*/
	void Room::makeConnection(pRoom room, int dir, lock_type lt, bool first = true) {
		if(room != NULL && first) {
			int dir2 = (dir + 2) % DIRECTIONS_N;
			room->makeConnection(this, dir2, lt, false);
		}
	}
	bool Room::setPosition_strong(pPhysical obj, Coordinate pos) {
		Coordinate pos_end = Coordinate(pos, obj->getSize());	//vertice del rettangolo opposto a pos
		pPhysical physical[ROOM_AREA];
		int found = MapHandler::checkRectangle(map, physical, pos, pos_end);
		bool valid = false;
		int i = 0;
		while(valid && i < found) {
			if(physical[i]->isInanimate() || physical[i]->getId() == ID_CHEST) valid = false;
			else physical[i]->destroy();	//distruggi oggetto se è character o projectile
			i++;
		}
		return valid;
	}
#pragma endregion SET_GET