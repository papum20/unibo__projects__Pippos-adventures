#include "health_potion.hpp"


HealthPotion::HealthPotion() : Artifact() {
	
}

HealthPotion::HealthPotion(const char n[], const char desc[]) : Artifact(n, desc) {
	healthGained = HEALTH_GAINED;
}

void HealthPotion::use_item(pItem item, int &stat) {
	//p->changeCurrentHealth(healthGained);
}