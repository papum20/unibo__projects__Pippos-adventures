#ifndef PLAYER_H
#define PLAYER_H



#include "character.hpp"



//il suo attacco dipende dall'arma


class Player : public Character {
	private:

	public:
		Player();

		void move(int input);
};




#endif