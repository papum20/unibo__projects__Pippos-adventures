#ifndef PLAYER_H
#define PLAYER_H



#include "character.hpp"



//il suo attacco dipende dall'arma


class Player : public Character {
	private:
//puntatore alla lista di array
p_animation_player head;
	public:
		Player();

		void move(int input);
};




#endif