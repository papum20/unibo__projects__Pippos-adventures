#ifndef BOSS_ROOM_HPP
#define BOSS_ROOM_HPP


#include "connected_room.hpp"



class BossRoom : public ConnectedRoom {
	private:
		// FUNZIONI
		void setDoorsUseable();								//rende porte utilizzabili se sono soddisfatte le condizioni (uccidere tutti i nemici nella stanza)
		// GENERAZIONE
		void generateEmpty();
		void addLevelDoor();
		// SPAWN
		pEnemy randEnemy(int level, pCharacter player);		//ritorna un nemico casuale
		// AUSILIARIE
		int doorsNumber();
		int randDoor();										//indice/direzione in cui generare porta
	
	public:
		BossRoom(Coordinate pos);

		void update(int input);
		void generate();
		void spawn(int level, pCharacter player, bool current = false);

		bool isBossRoom();
};





#endif