#ifndef ENEMY_HPP
#define ENEMY_HPP


#include "character.hpp"
#include "weapon.hpp"


//ha una sottoclasse per ogni tipo di nemico


class Enemy : public Character {
	protected:
		int points_given;
	public:
		Enemy();
		Enemy(int max_health, int max_stamina);
		void copy(Enemy B);			//copia i parametri di B

		void update(pMap map);
};


typedef Enemy *pEnemy;



#endif