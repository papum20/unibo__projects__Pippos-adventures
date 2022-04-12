#ifndef HEALTH_POTION_HPP
#define HEALTH_POTION_HPP


#include "powerup.hpp"
#include "player.hpp"
#define HEALTH_GAINED 10


class HealthPotion : public PowerUp {
	private:
		int healthGained;
	public:
		HealthPotion() : PowerUp();
		//costruttore
		void ChangeStats();
};





#endif