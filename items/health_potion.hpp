#ifndef HEALTH_POTION_HPP
#define HEALTH_POTION_HPP

#include "../artifact.hpp"

const char potion_description[description_length]="Pozione che ripristina 20 punti vita ";
const char potion_name[name_length]="Pozione della vita";

#define HEALTH_GAINED 20

class HealthPotion : public Artifact {
	private:
		int healthGained;				//valore di quanto incrementare la vita del player 
	public:
		HealthPotion();
		HealthPotion(const char n[], const char desc[]);

		void use_item(pItem item, int &stat, System_text* text);		//metodo che usa la pozione
};





#endif