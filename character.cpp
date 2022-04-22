#include "character.hpp"


Character::Character(int maxHealth) {
	
}


void Character::changeCurrentHealth(int delta) {
	curHealth += delta;
}