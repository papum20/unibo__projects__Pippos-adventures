#include "character.hpp"


Character::Character() : Physical() {
	is_attacking=false;
}

Character::Character(int maxH, int curH) : Physical() {
	maxHealth=maxH;
	curHealth=curH;
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

void Character::apply_equipment (){
	danno_fisico=(equipaggiamento->arma)->danno_fisico;
	danno_magico=(equipaggiamento->arma)->danno_magico;

	difesa_fisica=(equipaggiamento->scudo)->difesa_fisica+(equipaggiamento->armatura).difesa_fisica+(equipaggiamento->stivali).difesa_fisica;
	difesa_magica=(equipaggiamento->scudo)->difesa_magica+(equipaggiamento->armatura).difesa_magica+(equipaggiamento->collana).difesa_magica;
}

//FUNZIONI MOVIMENTO

void Character::setPosition(Coordinate pos) {
	this->pos = pos;
}

void Character::moveUp(pInanimate map[], pCharacter characters[]){
	Coordinate newpos=pos;
	newpos.y--;
	moveObject (map, characters, newpos);
	/*if (direction=='u')
		animation[move_up_index]=animation[move_up_index]->next; 
	else
		direction='u';
		animation[move_up_index]
	*/
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

//FUNZIONI COMBATTIMENTO

void calculate_damage(){
	pCharacter defender;
	defender=check_enemy_melee();
	if (defender!=NULL && defender.id!=id){
		defender->changeCurrentHealth(calculate_loss(defender));
	}
}

pCharacter Character::check_enemy_melee(){
	Coordinate start, end;
	switch (direction){
		case 'u':
			break;
		case 'd':
			break;
		case 'l':
			break;
		case 'r':
			break;
	}
	
	return (Room::checkLine(start, end));
}

void Character::calculate_loss(pCharacter c){
	return ( -(danno_fisico-(c->difesa_fisica/2)) + (danno_magico-(c->difesa_magica/2)));
}

void Character::changeCurrentHealth(int delta) {
	curHealth += delta;
}

#pragma region AUSILIARIE_GENERICHE
	void Character::swapPositions(pCharacter characters[], Coordinate a, Coordinate b) {
		pCharacter tmp = characters[a.single()];
		characters[a.single()] = characters[b.single()];
		characters[b.single()] = tmp;
	}
#pragma endregion AUSILIARIE_GENERICHE