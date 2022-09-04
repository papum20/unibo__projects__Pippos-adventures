#include "alive.hpp"


Alive::Alive() {
	maxHealth = 0;
	curHealth = 0;
}

Alive::Alive(int maxH, int curH) : Animate() {
	maxHealth=maxH;
	curHealth=curH;
}


void Alive::changeCurrentHealth(int delta) {
	curHealth += delta;
}