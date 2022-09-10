#include "boss_room.hpp"


BossRoom::BossRoom(Coordinate pos) : ConnectedRoom(pos) {

}

	void BossRoom::update(int input) {
		Room::update(input);
		setDoorsUseable();
	}
	void BossRoom::generate() {
		generateSidesWalls();		//muri laterali
		generateDoors();			//porte
		generateLevelDoor();		//porta per il prossimo livello
	}
	void BossRoom::spawn(int level, pCharacter player) {
		if(player != NULL) {
			player->setPosition(size.times(.5, .5).integer());
			addCharacter(player);
		}
		for(int i = 0; i < BOSSES_N[level]; i++) spawnEnemy(randEnemy(level, player));
	}

	void BossRoom::setDoorsUseable() {
		if(map->characters_n == 1) {						//se rimane solo il player
			for(int dir = 0; dir < DIRECTIONS_N; dir++)
				if(map->doors[dir] != NULL) map->doors[dir]->setUseable();
		}
	}



//// AUSILIARIE
#pragma region AUSILIARIE_PRINCIPALI

	void BossRoom::generateLevelDoor() {
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
		int rand_dir = rand() % doorsNumber();
		bool found = false;
		int dir = 0;
		while(!found && rand_dir > 0) {
			if(connected[dir] == NULL && rand_dir == 0) found = true;
			else {
				if(connected[dir] == NULL) rand_dir--;
				dir++;
			}
		}
		return dir;
	}

#pragma endregion AUSILIARIE SECONDARIE