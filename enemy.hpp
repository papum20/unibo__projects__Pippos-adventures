#ifndef ENEMY_HPP
#define ENEMY_HPP


#include "character.hpp"
#include "weapon.hpp"


//ha una sottoclasse per ogni tipo di nemico

const int enemy_stamina=50;

class Enemy : public Character {
	protected:
		int points_given;
		pCharacter player;
	public:
		Enemy();
		Enemy(pCharacter p);
		Enemy(int max_health, int max_stamina, int p_g, pCharacter p);
		void copyEnemy(Enemy B);			//copia i parametri di B

		void update(pMap map);
		void meleeIA(pMap map);
		void rangedIA(pMap map);
};


typedef Enemy* pEnemy;



#endif