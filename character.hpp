#ifndef CHARACTER_HPP
#define CHARACTER_HPP


#include "artifact.hpp"
#include "equipment/equipment.hpp"
#include "item_difensivi.hpp"
#include "physical.hpp"
#include "timer.hpp"
#include "weapon.hpp"
#include "door.hpp"
#include "map_handler.hpp"

//rappresenta un personaggio "vivente", come il giocatore o un qualsiasi nemico

const int W_NUMBER=10;
const int DEF_NUMBER=10;
const int PATH_LENGTH;

struct equipment {
	pWeapon arma;
	pShield scudo;
	pNecklace collana;
	pBoots stivali;
	pArmor armatura;
	pHelm elmo;
};

//class Character;
struct Map {
	Coordinate size;
	pPhysical physical[ROOM_AREA];
	pCharacter characters[ROOM_AREA];
	pDoor doors[MAX_CONNECTED_R];			//array di puntatori a porte (verso stanze collegate)
											//disposte in direzioni: 0=su, 1=destra, 2=giu, 3=sinistra, 4=segreta,all'interno
	pChest chests[ROOM_AREA];
};
typedef Map *pMap;



class Character : public Physical {
	private:
		//void swapPositions(Character *characters[], Coordinate a, Coordinate b);
		
	protected:

		bool is_attacking;
		int attack_counter;

		//variabili di movimento
		int idle_index;
		int move_up_index;
		int move_down_index;
		int move_left_index;
		int move_right_index;

		int attack_up_states;
		int attack_down_states;
		int attack_left_states;
		int attack_right_states;
		// ROOM
		//bool moveObject(pMap map[], Coordinate size, Coordinate move);	//muove di move se può, altrimenti ritorna false (se fuori mappa, se ob=inanimate/door, se non va su cella vuota..)

		equipment equipaggiamento;

		pWeapon weapons[W_NUMBER];
		int curr_weapon;

		pItem_def defensive_items[DEF_NUMBER];
		int last_def;
	public:
		int maxHealth;
		int curHealth;
		int danno_fisico;
		int danno_magico;
		int difesa_fisica;
		int difesa_magica;
		
		Character();
		Character(int maxH, int maxS);
		
		virtual void update(pMap map, int input);

		//FUNZIONI CHE MODIFICANO STATISTICHE
		void changeCurrentHealth(int delta);		//se delta positivo aumenta la vita corrente, se negativo la diminuisce
		void apply_equipment ();

		void moveUp(pMap map);
		void moveDown(pMap map);
		void moveLeft(pMap map);
		void moveRight(pMap map);

		//FUNZIONI COMBATTIMENTO

		pCharacter check_enemy_melee();
		void initiate_attack();
		void calculate_damage();
		int calculate_loss(pCharacter c);
		
};

typedef Character *pCharacter;



#endif