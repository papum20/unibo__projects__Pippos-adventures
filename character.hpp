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
const int PATH_LENGTH;

struct equipment {
	pWeapon arma;
	shield scudo;
	necklace collana;
	boots stivali;
	armor armatura;
};

class Character : public Physical {
	private:
		void swapPositions(Character *characters[], Coordinate a, Coordinate b);
		
	protected:
		int maxHealth;
		int curHealth;
		int danno_fisico;
		int danno_magico;
		int difesa_fisica;
		int difesa_magica;

		bool is_attacking;
		// ROOM
		bool moveObject(pInanimate map[], Character *characters[], Coordinate size, Coordinate move);	//muove di move se può, altrimenti ritorna false (se fuori mappa, se ob=inanimate/door, se non va su cella vuota..)

		char direction;					// u sopra, d sotto, l sinistra, r destra

		equipment equipaggiamento;

		pWeapon weapons[W_NUMBER];
		int curr_weapon;

		pItem_def defensive_items[DEF_NUMBER];
		int last_def;
	public:
		Character();
		Character(int maxH, int maxS);
		
		virtual void update(pInanimate map[], Character *characters[]);

		int findPath (Inanimate map[], Coordinate steps[], Coordinate start, Coordinate end);

		//FUNZIONI CHE MODIFICANO STATISTICHE
		void changeCurrentHealth(int delta);		//se delta positivo aumenta la vita corrente, se negativo la diminuisce
		void apply_equipment ();

		void setPosition(Coordinate pos);

		void moveUp(pInanimate map[], pCharacter characters[]);
		void moveDown(pInanimate map[], pCharacter characters[]);
		void moveLeft(pInanimate map[], pCharacter characters[]);
		void moveRight(pInanimate map[], pCharacter characters[]);
};

typedef Character *pCharacter;



#endif