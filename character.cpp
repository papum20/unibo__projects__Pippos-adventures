#include "character.hpp"


Character::Character() : Physical() {
	
}

Character::Character(int maxHealth) : Physical() {
	
}


void Character::changeCurrentHealth(int delta) {
	curHealth += delta;
}