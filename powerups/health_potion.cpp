#include "health_potion.hpp"


HealthPotion::HealthPotion() : PowerUp() {
	healthGained = HEALTH_GAINED;
}

void HealthPotion::ChangeStats() {
	player.changeCurrentHealth(healthGained);
}