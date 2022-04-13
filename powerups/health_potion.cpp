#include "health_potion.hpp"


HealthPotion::HealthPotion() {
	healthGained = HEALTH_GAINED;
}

void HealthPotion::ChangeStats() {
	player.changeCurrentHealth(healthGained);
}