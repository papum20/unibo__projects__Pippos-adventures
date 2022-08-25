#ifndef ENEMY_HPP
#define ENEMY_HPP


#include "character.hpp"
#include "weapon.hpp"

const int ANIMATION_WIDTH = 20;
const int ANIMATION_HEIGHT = 20;

//ha una sottoclasse per ogni tipo di nemico


class Enemy : public Character {
	private:
		int points_given;
	public:
		Enemy(int max_health, int max_stamina, int p_g);

		void update(pInanimate map[], pCharacter characters[]);
};


typedef Enemy *pEnemy;



#endif