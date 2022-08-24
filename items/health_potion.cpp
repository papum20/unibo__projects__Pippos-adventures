#include "health_potion.hpp"


HealthPotion::HealthPotion() : Artifact() {
	healthGained = HEALTH_GAINED;
}

void HealthPotion::use_item(pPlayer p) {
	player->changeCurrentHealth(healthGained);
}