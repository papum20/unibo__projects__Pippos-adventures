#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "physical.hpp"



class Character : public Physical {
	private:
		int maxHealth;
		int curHealth;
	protected:

	public:
		Character(int maxHealth);

		//FUNZIONI CHE MODIFICANO STATISTICHE
		void changeCurrentHealth(int delta);		//se delta positivo aumenta la vita corrente, se negativo la diminuisce
};





#endif