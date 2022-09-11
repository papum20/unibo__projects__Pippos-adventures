#include "health_potion.hpp"


HealthPotion::HealthPotion() : Artifact() {
	//strcpy(rarity, common);
	id=ID_HEALTH_POTION;
	healthGained = HEALTH_GAINED;
	strcpy (name, potion_name);
	strcpy (description, potion_description);
}


void HealthPotion::use_item(pItem item, int &stat, System_text* text) {
	if (stat+healthGained>=p_max_health){
		stat=p_max_health;
		text->insert_string(life_max);
	}
	else{
		stat=stat+healthGained;
		text->insert_string(gain_life);
	}
}