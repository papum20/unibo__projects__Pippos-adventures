#ifndef HEALTH_POTION_HPP
#define HEALTH_POTION_HPP


#include "../powerup.hpp"
#define HEALTH_GAINED 10


class HealthPotion : public PowerUp {
	private:
		int healthGained;				//valore di quanto incrementare la vita del player 
	public:
		HealthPotion();

		void use_item(Player p);		//metodo che usa la pozione
};





#endif