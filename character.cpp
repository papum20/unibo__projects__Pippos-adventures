#include "character.hpp"


Character::Character() {
	
}


void Character::changeCurrentHealth(int delta) {
	curHealth += delta;
}