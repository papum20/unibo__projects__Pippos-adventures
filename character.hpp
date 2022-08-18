#ifndef CHARACTER_HPP
#define CHARACTER_HPP


#include "inanimate.hpp"
#include "physical.hpp"
#include "timer.hpp"
#include "weapon.hpp"
#include "artifact.hpp"
#include "item_difensivi.hpp"

//rappresenta un personaggio "vivente", come il giocatore o un qualsiasi nemico

const int W_NUMBER=10;
const int DEF_NUMBER=10;

class Character : public Physical {
	private:
		void swapPositions(Character *characters[], Coordinate a, Coordinate b);
		
	protected:
		int maxHealth;
		int curHealth;
		int physical_attack;
		int magical_attack;
		int physical_defense;
		int magical_defense;

		bool is_attacking;
		// ROOM
		bool moveObject(pInanimate map[], Character *characters[], Coordinate size, Coordinate move);	//muove di move se può, altrimenti ritorna false (se fuori mappa, se ob=inanimate/door, se non va su cella vuota..)
		//indici utili per calcoli collisioni e direzionalità
		int up_attack_index;
		int down_attack_index;
		int left_attack_index;
		int right_attack_index;

		char direction;					// u sopra, d sotto, l sinistra, r destra

		pWeapon weapons[W_NUMBER];
		int curr_weapon;

		pItem_def defensive_items[DEF_NUMBER];
		int last_def;
	public:
		Character();
<<<<<<< HEAD
		Character(int maxH, int maxS);
		
		virtual void update(pInanimate map[], Character *characters[]);
=======
		Character(int maxH, int curH, int physical_attack, int magical_attack, int physical_defense, int magical_defense);
		void update(pInanimate map[], Character *characters[], char input);
>>>>>>> fb4f651e184bfd16672f61564053bb3afbd27a25

		//FUNZIONI CHE MODIFICANO STATISTICHE
		void changeCurrentHealth(int delta);		//se delta positivo aumenta la vita corrente, se negativo la diminuisce

		void setPosition(Coordinate pos);

		void moveUp(pInanimate map[], pCharacter characters[]);
		void moveDown(pInanimate map[], pCharacter characters[]);
		void moveLeft(pInanimate map[], pCharacter characters[]);
		void moveRight(pInanimate map[], pCharacter characters[]);
};

typedef Character *pCharacter;



#endif