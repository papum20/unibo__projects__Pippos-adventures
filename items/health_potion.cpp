#include "health_potion.hpp"


HealthPotion::HealthPotion(const char n[], const char desc[]) : Artifact(n, desc) {
	healthGained = HEALTH_GAINED;
}

void HealthPotion::use_item(pPlayer p) {
	p->changeCurrentHealth(healthGained);
}