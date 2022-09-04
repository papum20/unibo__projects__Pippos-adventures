#include "alive.hpp"


Alive::Alive() {
	maxHealth = 0;
	curHealth = 0;
}

Alive::Alive(int maxH, int curH) : Animate() {
	maxHealth=maxH;
	curHealth=curH;
}

void Alive::copyAlive(Alive B) {
	maxHealth=B.maxHealth;
	curHealth=B.curHealth;
	difesa_fisica = B.difesa_fisica;
	difesa_magica=B.difesa_magica;
	copyAnimate(B);
}

void Alive::changeCurrentHealth(int delta) {
	curHealth += delta;
}