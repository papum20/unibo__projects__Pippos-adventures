#include "character.hpp"


Character::Character() : Physical() {
	
}

Character::Character(int maxH, int curH) : Physical() {
	maxHealth=maxH;
	curHealth=curH;
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

void Character::update(pInanimate map[], pCharacter characters[], char input){
	Coordinate newpos= pos;
	switch (input)
	{
	case KEY_UP:{
		newpos.y--;
		moveObject (map, characters, newpos);
	}
	case KEY_DOWN:{
		newpos.y++;
		moveObject (map, characters, newpos);
	}	
	case KEY_LEFT:{
		newpos.x--;
		moveObject (map, characters, newpos);
	}
	case KEY_RIGHT:{
		newpos.x++;
		moveObject (map, characters, newpos);
	}
	
	case {//tasto per aprire il menu:
		menu.open();
	}
	case {//tasto per colpire
		//funzioni combat system
	}	
	}

}

#pragma region AUSILIARIE_GENERICHE
	void Character::swapPositions(pCharacter characters[], Coordinate a, Coordinate b) {
		pCharacter tmp = characters[a.single()];
		characters[a.single()] = characters[b.single()];
		characters[b.single()] = tmp;
	}
#pragma endregion AUSILIARIE_GENERICHE