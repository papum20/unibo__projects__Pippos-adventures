#ifndef ENEMY_HPP
#define ENEMY_HPP


#include "character.hpp"


//ha una sottoclasse per ogni tipo di nemico


class Enemy : public Character {
	private:

	public:
		Enemy();
		Enemy(int max_health);
};


typedef Enemy *pEnemy;



#endif