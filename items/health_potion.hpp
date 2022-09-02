#ifndef HEALTH_POTION_HPP
#define HEALTH_POTION_HPP

#include "../artifact.hpp"

#define HEALTH_GAINED 10

class HealthPotion : public Artifact {
	private:
		int healthGained;				//valore di quanto incrementare la vita del player 
	public:
		HealthPotion();
		HealthPotion(const char n[], const char desc[]);

		void use_item(pPlayer p);		//metodo che usa la pozione
};





#endif