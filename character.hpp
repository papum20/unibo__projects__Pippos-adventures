#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "physical.hpp"
#include "weapon.hpp"

//rappresenta un personaggio "vivente", come il giocatore o un qualsiasi nemico


class Character : public Physical {
	private:
		
	protected:
		int maxHealth;
		int curHealth;
		Weapon currWeapon;
	public:
		Character(int maxHealth, Weapon currWeapon);

		//FUNZIONI CHE MODIFICANO STATISTICHE
		void changeCurrentHealth(int delta);		//se delta positivo aumenta la vita corrente, se negativo la diminuisce
};


#endif