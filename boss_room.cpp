#include "boss_room.hpp"


BossRoom::BossRoom(Coordinate pos) : ConnectedRoom(pos) {
	size = Coordinate(ROOM_BOSS_WIDTH, ROOM_BOSS_HEIGHT);
	map->size = size;
}

	void BossRoom::update(int input) {

		Room::update(input);
		setDoorsUseable();
	}
	void BossRoom::generate() {
		generateEmpty();			//solo muri laterali e pavimento
		addLevelDoor();				//porta per il prossimo livello
		generateDoors();			//porte
	}
	void BossRoom::spawn(int level, pCharacter player, bool current) {
		if(current && player != NULL) {
			player->setPosition(size.times(.5, .5).integer());
			addCharacter(player);
		}
		for(int i = 0; i < BOSSES_N[level]; i++) spawnEnemy(randEnemy(level, player));
	}

	void BossRoom::setDoorsUseable() {
		if(map->characters_n == 1) {						//se rimane solo il player
			for(int dir = 0; dir < DIRECTIONS_N; dir++)
				if(map->doors[dir] != NULL && map->doors[dir]->isBoss()) map->doors[dir]->setUseable();
		}
	}



//// AUSILIARIE
#pragma region AUSILIARIE_PRINCIPALI

	void BossRoom::generateEmpty() {
		Coordinate i = Coordinate(0, 0, size);
		do {
			if(!i.inBounds(COORDINATE_ONE.times(ROOM_BOSS_WALL_DEPTH, ROOM_BOSS_WALL_DEPTH), Coordinate(size, COORDINATE_NEGATIVE.times(ROOM_BOSS_WALL_DEPTH, ROOM_BOSS_WALL_DEPTH)))) map->physical[i.single()] = WALL_INSTANCE;
			else map->physical[i.single()] = FLOOR_INSTANCE;
			i.next();
		} while(!i.equals(COORDINATE_ZERO));
	}
	void BossRoom::addLevelDoor() {
		addDoor(randDoor(), LOCK_NONE, true);
	}
	pEnemy BossRoom::randEnemy(int level, pCharacter player) {
		int r = rand() % BOSSES_CHANCE_TOT[level];
		int i = 0, counter = 0;
		while(r >= counter + BOSSES_CHANCHES[level][i]) {
			counter += BOSSES_CHANCHES[level][i];
			i++;
		}
		pEnemy res = new Enemy(player);
		res->copyEnemy(BOSSES_INSTANCES[level][i]);
		return res;
	}

#pragma endregion AUSILIARIE_PRINCIPALI


#pragma region AUSILIARIE_SECONDARIE

	int BossRoom::doorsNumber() {
		int doors = 0;
		for(int dir = 0; dir < DIRECTIONS_N; dir++)
			if(connected[dir] != NULL) doors++;
		return doors;
	}
	int BossRoom::randDoor() {
		// per come genera level la stanza, è garantito che ci sia sempre almeno uno spazio per una porta
		int rand_dir = rand() % (DIRECTIONS_N - doorsNumber());
		bool found = false;
		int dir = 0;
		while(!found && rand_dir > 0 && connected[dir] != NULL) {
			if(connected[dir] == NULL && rand_dir == 0) found = true;
			else {
				if(connected[dir] == NULL) rand_dir--;
				dir++;
			}
		}
		return dir;
	}

#pragma endregion AUSILIARIE SECONDARIE





	bool BossRoom::isBossRoom() {
		return true;
	}