#include "character.hpp"


Character::Character() : Physical() {
	
}

Character::Character(int maxH, int maxS) : Physical() {
	maxHealth=maxH;
	curHealth=maxH;
	maxStamina=maxS;
	curStamina=maxS;
	is_attacking=false;
}


bool Character::moveObject(pInanimate map[], pCharacter characters[], Coordinate move) {
	Coordinate newPos = Coordinate(pos, move);
	if(newPos.inBounds(Coordinate(0, 0), size) || map[newPos.single()]->getId() != ID_FLOOR)
		return false;
	else {
		swapPositions(characters, newPos, pos);
		return true;
	}
}


void Character::changeCurrentHealth(int delta) {
	curHealth += delta;
}

void Character::setPosition(Coordinate pos) {
	this->pos = pos;
}

void Character::moveUp(pInanimate map[], pCharacter characters[]){
	Coordinate newpos=pos;
	newpos.y--;
	moveObject (map, characters, newpos);
	direction='u';
}

void Character::moveDown(pInanimate map[], pCharacter characters[]){
	Coordinate newpos=pos;
	newpos.y++;
	moveObject (map, characters, newpos);
	direction='d';
}

void Character::moveLeft(pInanimate map[], pCharacter characters[]){
	Coordinate newpos=pos;
	newpos.x--;
	moveObject (map, characters, newpos);
	direction='l';
}

void Character::moveRight(pInanimate map[], pCharacter characters[]){
	Coordinate newpos=pos;
	newpos.x++;
	moveObject (map, characters, newpos);
	direction='r';
}

#pragma region AUSILIARIE_GENERICHE
	void Character::swapPositions(pCharacter characters[], Coordinate a, Coordinate b) {
		pCharacter tmp = characters[a.single()];
		characters[a.single()] = characters[b.single()];
		characters[b.single()] = tmp;
	}
#pragma endregion AUSILIARIE_GENERICHE