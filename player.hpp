#ifndef PLAYER_H
#define PLAYER_H



#include "character.hpp"



//il suo attacco dipende dall'arma
//inizializzo i vari array di player della struttura

class Player : public Character {
	private:
//puntatore alla lista di array
	public:
		Player();

		void move(int input);
};




#endif