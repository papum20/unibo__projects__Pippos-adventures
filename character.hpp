#ifndef CHARACTER_HPP
#define CHARACTER_HPP


#include "inanimate.hpp"
#include "physical.hpp"
#include "timer.hpp"


//rappresenta un personaggio "vivente", come il giocatore o un qualsiasi nemico


class Character : public Physical {
	private:
		void swapPositions(Character *characters[], Coordinate a, Coordinate b);
		
	protected:
		int maxHealth;
		int curHealth;

		// ROOM
		bool moveObject(pInanimate map[], Character *characters[], Coordinate size, Coordinate move);	//muove di move se può, altrimenti ritorna false (se fuori mappa, se ob=inanimate/door, se non va su cella vuota..)
	public:
		Character();
		Character(int maxHealth);
		void update();

		//FUNZIONI CHE MODIFICANO STATISTICHE
		void changeCurrentHealth(int delta);		//se delta positivo aumenta la vita corrente, se negativo la diminuisce

		void setPosition(Coordinate pos);
};

typedef Character *pCharacter;



#endif