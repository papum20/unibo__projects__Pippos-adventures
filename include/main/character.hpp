#ifndef CHARACTER_HPP
#define CHARACTER_HPP


#include "main/weapon.hpp"
#include "main/item_difensivi.hpp"
#include "equipment/equipment.hpp"
#include "main/system_text.hpp"


//rappresenta un personaggio "vivente", come il giocatore o un qualsiasi nemico

const int W_NUMBER=6;
const int DEF_NUMBER=11;
const int stamina_cost=10;
const int stamina_gain=5;

struct equipment {
	pWeapon arma;
	pItem_def scudo;
	pItem_def collana;
	pItem_def stivali;
	pItem_def armatura;
	pItem_def elmo;
};


#include "main/alive.hpp"
#include "main/artifact.hpp"


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

	public:
		int danno_fisico;
		int danno_magico;
		int weapon_attacking_index;
		Character();
		Character(int maxH, int maxS);
		void copyCharacter(Character B);
		
		virtual void update(pMap map);
		virtual void drawAtPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate win_size, Coordinate pos);	//disegna l'oggetto nella finestra, alle date coordinate, secondo la sua animazione, entro i limiti della finestra
		void destroyInstance(pMap map);
		//precondizione: da richiamare con coordinate giuste

		//FUNZIONI CHE MODIFICANO STATISTICHE
		void initialize_equipment();
		void apply_equipment ();

		void change_helm(pItem_def h);
		void change_weapon(pWeapon w);
		void change_necklace (pItem_def n);
		void change_armor (pItem_def a);
		void change_boots (pItem_def b);
		void change_shield (pItem_def s);
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


#include "main/door.hpp"
#include "main/projectile.hpp"
#include "main/timer.hpp"



#endif