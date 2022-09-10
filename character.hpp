#ifndef CHARACTER_HPP
#define CHARACTER_HPP


#include "weapon.hpp"
#include "item_difensivi.hpp"
#include "equipment/equipment.hpp"


//rappresenta un personaggio "vivente", come il giocatore o un qualsiasi nemico

const int W_NUMBER=10;
const int DEF_NUMBER=15;

struct equipment {
	pWeapon arma;
	pShield scudo;
	pNecklace collana;
	pBoots stivali;
	pArmor armatura;
	pHelm elmo;
};


#include "alive.hpp"
#include "artifact.hpp"


class Character : public Alive {
		
	protected:

		bool is_attacking;
		int attack_counter;				//variabile che contiene il contatore a cui l'animazione fa danno
		int attacking_states;			//variabiile che contiene il numero di animazioni d'attacco
		//variabili di movimento
		int attack_up_states;
		int attack_down_states;
		int attack_right_states;
		int attack_left_states;

		equipment equipaggiamento;

		pWeapon weapons[W_NUMBER];
		int weapons_n;
		int curr_weapon;

		pItem_def defensive_items[DEF_NUMBER];
		int defensive_items_n;
		int last_def;
	public:
		int danno_fisico;
		int danno_magico;
		int weapon_attacking_index;
		Character();
		Character(int maxH, int maxS);
		void copyCharacter(Character B);
		
		virtual void update(pMap map);
		virtual void drawAtPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate win_size, Coordinate pos);	//disegna l'oggetto nella finestra, alle date coordinate, secondo la sua animazione, entro i limiti della finestra
		void destroy(pMap map);
		//precondizione: da richiamare con coordinate giuste

		//FUNZIONI CHE MODIFICANO STATISTICHE
		void initialize_equipment();
		void apply_equipment ();

		void change_helm(pHelm h);
		void change_weapon(pWeapon w);
		void change_necklace (pNecklace n);
		void change_armor (pArmor a);
		void change_boots (pBoots b);
		void change_shield (pShield s);
		virtual int getPoints();
		
		//FUNZIONI MOVIMENTO

		void moveUp(pMap map);
		void moveDown(pMap map);
		void moveLeft(pMap map);
		void moveRight(pMap map);

		//FUNZIONI COMBATTIMENTO
		virtual void change_points(int delta);
		virtual void check_enemy_melee(pMap map);
		void initiate_attack();
		void ranged_attack(pMap map);
		int calculate_damage(Alive *c);


		equipment *getEqipment();
		
};

typedef Character *pCharacter;


#include "door.hpp"
#include "projectile.hpp"
#include "timer.hpp"



#endif