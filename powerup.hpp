#ifndef POWERUP_H
#define POWERUP_H


#include "item.hpp"
#include "player.hpp"



//oggetti che aumentano statistiche, guariscono, attivano la possibilità di usare abilità (schivata...)
//ha una sotto-classe per ognuno di questi oggetti

class PowerUp : public Item {
	protected:
		Player player;

	public:
		PowerUp() : Item() {};

		void ChangeStats();
};





#endif