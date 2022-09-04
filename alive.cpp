#include "alive.hpp"


Alive::Alive() {
	maxHealth = 0;
	curHealth = 0;
	maxStamina = 0;
	curStamina = 0;
}

Alive::Alive(int maxH, int maxS) : Animate() {
	maxHealth=maxH;
	maxStamina=maxS;
	curHealth=maxHealth;
	curStamina=maxStamina;
}

void Alive::copyAlive(Alive B) {
	maxHealth=B.maxHealth;
	curHealth=B.curHealth;
	maxStamina=B.maxHealth;
	curStamina=B.curStamina;
	difesa_fisica = B.difesa_fisica;
	difesa_magica=B.difesa_magica;
	copyAnimate(B);
}

void Alive::changeCurrentHealth(int delta) {
	curHealth += delta;
}