#ifndef ALIVE_HPP
#define ALIVE_HPP


#include "animate.hpp"


class Alive : public Animate {
	protected:
	public:
		int maxHealth;
		int curHealth;
		int maxStamina;
		int curStamina;
		int difesa_fisica;
		int difesa_magica;

		Alive();
		Alive(int maxH, int maxS);
		void copyAlive(Alive B);

		int getHealth();

		virtual void changeCurrentHealth(int delta);		//se delta positivo aumenta la vita corrente, se negativo la diminuisce
};

typedef Alive *pAlive;


#endif