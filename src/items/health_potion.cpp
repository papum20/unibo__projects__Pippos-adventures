#include "health_potion.hpp"


HealthPotion::HealthPotion() : Artifact() {
	//strcpy(rarity, common);
	id=ID_HEALTH_POTION;
	//healthGained = HEALTH_GAINED;
	increment = HEALTH_GAINED;
	max_stat = p_max_health;
	strcpy (name, potion_name);
	strcpy (description, potion_description);
	strcpy(text_error, life_max);
	strcpy(text_success, gain_life);
}

