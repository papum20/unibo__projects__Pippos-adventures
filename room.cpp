#include "room.hpp"


#pragma region MAIN
	Room::Room(Coordinate pos) {
		//inzializza stanza
		this->pos = pos;
		scale_x = SCALE_X;

		floorInstance = new Floor();
		wallInstance = new Wall();

		map = new Map(scale_x, floorInstance, wallInstance);
	}
	void Room::recursiveDestroy() {
		map->destroy();
		delete this;
	}

	void Room::update(char input) {
		map->update_all(input);
	}

	void Room::generate() {
		map->generate();
	}

	void Room::spawnEnemy(pEnemy enemy) {
		s_coord available[ROOM_AREA];
		int av_size = getFreeCells(available, enemy->getSize());
		if(av_size > 0) {
			enemy->setPosition(Coordinate(available[rand() % av_size], map->getSize()));
			map->addCharacter(enemy);
		}
	}
	void Room::spawnChest(pChest chest) {
		s_coord available[ROOM_AREA];
		int av_size = getFreeCells(available, chest->getSize());
		if(av_size > 0) {
			chest->setPosition(Coordinate(available[rand() % av_size], map->getSize()));
			map->addChest(chest);
		}
	}

	void Room::draw(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_size, Coordinate center) {
		//disegna dall'alto al basso, da sinistra a destra, così si mantiene la prospettiva quando un oggetto che si trova davanti ad un altro gli viene disegnato davanti
		Coordinate wstart = Coordinate(center.x - win_size.x / 2, center.y - win_size.y / 2), wend = Coordinate(center.x + Math::ceil(win_size.x / 2.), center.y + Math::ceil(win_size.y / 2.));
		Coordinate i = Coordinate(wstart, wstart, wend);
		do {
			pPhysical obj = map->checkPosition(i);
			if(obj->isInanimate()) obj->drawAtPosition(scr, win_size, i);
			else {
				obj->drawAtOwnPosition(scr, win_size);
				floorInstance->drawAtPosition(scr, win_size, i);
			}
			i.next();
		} while(!i.equals(wstart));
	}
#pragma endregion MAIN


#pragma region AUSILIARIE
	int Room::getFreeCells(s_coord available[], Coordinate size) {
		int length = 0;
		Coordinate i = Coordinate(Coordinate(0, 0), map->getSize());
		do {
			if(map->isFreeSpace(i, Coordinate(i, size))) {
				available[length] = i.single();
				length++;
			}

		} while(!i.equals(Coordinate(0, 0)));
		return length;
	}
#pragma endregion AUSILIARE


#pragma region SET_GET
//// GET
	Coordinate Room::getPos() {
		return pos;
	}
	Coordinate Room::getSize() {
		return map->getSize();
	}
	void Room::getMap(pPhysical map[], Coordinate &size) {
		for(s_coord i = 0; i < this->map->getSize().x / scale_x * this->map->getSize().y; i++) map[i] = this->map->checkPosition(Coordinate(i * scale_x, this->map->getSize()));
		size = this->map->getSize().times(1. / scale_x, 1);
	}
	void Room::makeConnection(pRoom room, int dir, lock_type lt, bool first = true) {
		if(room != NULL && first) {
			int dir2 = (dir + 2) % DIRECTIONS_N;
			room->makeConnection(this, dir2, lt, false);
		}
	}
	bool Room::setPosition_strong(pPhysical obj, Coordinate pos) {
		Coordinate pos_end = Coordinate(pos, obj->getSize());	//vertice del rettangolo opposto a pos
		pPhysical physical[ROOM_AREA];
		int found = map->checkRectangle(physical, pos, pos_end);
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