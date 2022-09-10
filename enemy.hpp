#ifndef ENEMY_HPP
#define ENEMY_HPP


#include "character.hpp"
#include "weapon.hpp"



//ha una sottoclasse per ogni tipo di nemico

const int enemy_stamina=50;
const int enemy_refreshing_rate=3;
const int chase_distance=20;
const int enemy_vision=30;
const int initial_step=0;
const int max_steps=enemy_refreshing_rate*2;

class Enemy : public Character {
	protected:
		int attack_counter;
		int points_given;
		pCharacter player;
		Coordinate memorized_path[max_steps];
		bool player_in_vision;
		bool player_found;
		int frames_passed;
		int memorized_steps;
		int current_step;
	public:
		Enemy();
		Enemy(pCharacter p);
		Enemy(int max_health, int max_stamina, int p_g, pCharacter p);
		void destroy(pMap map);
		void copyEnemy(Enemy B);			//copia i parametri di B

		void make_step(pMap map);
		void update(pMap map);
		void check_enemy_melee(pMap map);
		void meleeIA(pMap map);
		void rangedIA(pMap map);
		int getPoints();
};


typedef Enemy* pEnemy;



#endif