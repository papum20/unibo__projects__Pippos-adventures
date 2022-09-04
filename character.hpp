#ifndef CHARACTER_HPP
#define CHARACTER_HPP


#include "weapon.hpp"
#include "item_difensivi.hpp"
#include "equipment/equipment.hpp"


//rappresenta un personaggio "vivente", come il giocatore o un qualsiasi nemico

const int W_NUMBER=10;
const int DEF_NUMBER=10;

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
	private:
		//void swapPositions(Character *characters[], Coordinate a, Coordinate b);
		
	protected:

		bool is_attacking;
		int attack_counter;				//variabile che contiene il contatore a cui l'animazione fa danno
		int attacking_states;			//variabiile che contiene il numero di animazioni d'attacco
		//variabili di movimento
		int idle_index;
		int move_up_index;
		int move_down_index;
		int move_left_index;
		int move_right_index;

		int attack_up_states;
		int attack_down_states;
		int attack_right_states;
		int attack_left_states;

		// ROOM
		//bool moveObject(pMap map[], Coordinate size, Coordinate move);	//muove di move se può, altrimenti ritorna false (se fuori mappa, se ob=inanimate/door, se non va su cella vuota..)

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
	
		Character();
		Character(int maxH, int maxS);
		void copyCharacter(Character B);
		
		virtual void update(pMap map);
		virtual void drawAtPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate win_size, Coordinate pos);	//disegna l'oggetto nella finestra, alle date coordinate, secondo la sua animazione, entro i limiti della finestra
		//precondizione: da richiamare con coordinate giuste

		//FUNZIONI CHE MODIFICANO STATISTICHE
		void apply_equipment ();

		void moveUp(pMap map);
		void moveDown(pMap map);
		void moveLeft(pMap map);
		void moveRight(pMap map);

		//FUNZIONI COMBATTIMENTO

		void check_enemy_melee(pMap map);
		void initiate_attack();
		int calculate_damage(Alive *c);

		equipment *getEqipment();
		
};

typedef Character *pCharacter;


#include "door.hpp"
#include "projectile.hpp"
#include "timer.hpp"



#endif