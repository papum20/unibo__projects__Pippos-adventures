#ifndef ENEMY_HPP
#define ENEMY_HPP


#include "character.hpp"
#include "weapon.hpp"

const int ENEMY_ANIMATION_WIDTH = 20;
const int ENEMY_ANIMATION_HEIGHT = 20;

//ha una sottoclasse per ogni tipo di nemico


class Enemy : public Character {
	private:
		int points_given;
	public:
		Enemy();
		Enemy(int max_health, int max_stamina, int p_g);
		void copy(Enemy B);			//copia i parametri di B

		void update(pMap map);
};


typedef Enemy *pEnemy;



#endif