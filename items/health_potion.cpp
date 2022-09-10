#include "health_potion.hpp"


HealthPotion::HealthPotion() : Artifact() {
	//strcpy(rarity, common);
	id=ID_HEALTH_POTION;
	healthGained = HEALTH_GAINED;
	strcpy (name, potion_name);
	strcpy (description, potion_description);
}


void HealthPotion::use_item(pItem item, int &stat) {
	if (stat+healthGained>=p_max_health)
		stat=p_max_health;
	else
		stat=stat+healthGained;
}