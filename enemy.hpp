#ifndef ENEMY_HPP
#define ENEMY_HPP


#include "character.hpp"


//ha una sottoclasse per ogni tipo di nemico


class Enemy : public Character {
	private:

	public:
		Enemy(int max_health, int max_stamina);

		void update(pInanimate map[], pCharacter characters[]);
};


typedef Enemy *pEnemy;



#endif