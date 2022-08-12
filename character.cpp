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

/*void Character::update (pInanimate map[], pCharacter characters[], char input){
	
	update_movement(map, characters, input);

}*/
void Character::update(pInanimate map[], pCharacter characters[], char input){
	Coordinate newpos= pos;
	switch (input)
	{
	case 'w':{
		newpos.y--;
		moveObject (map, characters, newpos);
		break;
	}
	case 's':{
		newpos.y++;
		moveObject (map, characters, newpos);
		break;
	}	
	case 'a':{
		newpos.x--;
		moveObject (map, characters, newpos);
		break;
	}
	case 'd':{
		newpos.x++;
		moveObject (map, characters, newpos);
		break;
	}
	case 'm' {
		open_menu();
		break;
	}
	case 'n' {
		open_inventary();
		break;
	}
	case ctrl(a){
		//iter animazione attacco a sinistra
	}
	case ctrl(s){
		//iter animazione attacco in basso
	}
	case ctrl(d){
		//iter animazione attacco a destra
	}
	case ctrl(w){
		//iter animazione attaco in alto
	}
	}

}

void Character::mvup(){
	Coordinate newpos=pos;
	newpos.y--;
	moveObject (map, characters, newpos);
}

#pragma region AUSILIARIE_GENERICHE
	void Character::swapPositions(pCharacter characters[], Coordinate a, Coordinate b) {
		pCharacter tmp = characters[a.single()];
		characters[a.single()] = characters[b.single()];
		characters[b.single()] = tmp;
	}
#pragma endregion AUSILIARIE_GENERICHE