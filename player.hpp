#ifndef PLAYER_H
#define PLAYER_H



#include "character.hpp"



//il suo attacco dipende dall'arma


class Player : public Character {
	private:

	public:
		Player() : Character();

		void move(int input);
};




#endif