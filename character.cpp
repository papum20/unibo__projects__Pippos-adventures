#include "character.hpp"


Character::Character() : Physical() {
	is_attacking=false;
	apply_equipment();
}

Character::Character(int maxH, int curH) : Physical() {
	maxHealth=maxH;
	curHealth=curH;
	is_attacking=false;
	apply_equipment();
}

void Character::update(pMap map) {
	Physical::update(map);
}

void Character::drawAtPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate win_size, Coordinate pos) {
	Animation a_weapon = weapons[curr_weapon]->getCurrentAnimation();
	Coordinate draw_start = Coordinate(pos, weapons[curr_weapon]->getOffset().negative());
	Coordinate draw_end = Coordinate(draw_start, a_weapon.size);
	Coordinate character_start = pos, character_end = Coordinate(character_start, getCurrentAnimation().size);
	Coordinate win_end = Coordinate(win_start, win_size);

	Coordinate relative = Coordinate(0, 0, a_weapon.size);										//coordinata relativa all'animazione, all'interno di essa
	do {
		Coordinate global = Coordinate(Coordinate(relative, draw_start), win_start, win_end);	//coordinata globale di relative, sulla mappa
		if(global.inOwnBounds()) {												//se il punto è interno alla finestra da disegnare
			if(global.inBounds(character_start, character_end))
			//se il punto dell'animazione è vuoto o contiene il carattere speciale: disegna personaggio
			if(a_weapon.state[relative.single()] == CHAR_EMPTY || a_weapon.state[relative.single()] == CHAR_WEAPON_MASK) scr[]
			//altrimenti: disegna arma
		}
	} while(!relative.equals(draw_start));
}


/*bool Character::map->move(pMap  Coordinate move) {
	Coordinate newPos = Coordinate(pos, move);
	if(newPos.inBounds(Coordinate(0, 0), size) || map[newPos.single()]->getId() != ID_FLOOR)
		return false;
	else {
		swapPositions(this, newPos, pos);
		return true;
	}
}*/

void Character::apply_equipment (){
	if ((equipaggiamento.arma)!=NULL){
		danno_fisico=(equipaggiamento.arma)->danno_fisico;
		danno_magico=(equipaggiamento.arma)->danno_magico;	
	}

	if ((equipaggiamento.armatura)!=NULL){
		difesa_fisica=difesa_fisica+(equipaggiamento.armatura)->difesa_fisica;
		difesa_magica=difesa_magica+(equipaggiamento.armatura)->difesa_magica;
	}

	if ((equipaggiamento.scudo)!=NULL){
		difesa_fisica=difesa_fisica+(equipaggiamento.scudo)->difesa_fisica;
		difesa_magica=difesa_magica+(equipaggiamento.scudo)->difesa_magica;
	}

	if ((equipaggiamento.stivali)!=NULL){
		difesa_fisica=difesa_fisica+(equipaggiamento.stivali)->difesa_fisica;
	}

	if ((equipaggiamento.collana)!=NULL){
		difesa_magica=difesa_magica+(equipaggiamento.collana)->difesa_magica;
	}

	if ((equipaggiamento.elmo!=NULL)){
		difesa_fisica=difesa_fisica+(equipaggiamento.elmo)->difesa_fisica;;
	}
}

//FUNZIONI MOVIMENTO

void Character::moveUp(pMap map){
	Physical::moveDown(map);
	if (current_animation==move_up_index){
		animations[current_animation]=animations[current_animation]->next;
	}
	else{
		current_animation=move_up_index;
		direction='u';
	}
}

void Character::moveDown(pMap map){
	Physical::moveDown(map);
	if (current_animation==move_down_index){
		animations[current_animation]=animations[current_animation]->next;
	}
	else{
		current_animation=move_down_index;
		direction='d';
	}
}

void Character::moveLeft(pMap map){
	Physical::moveDown(map);
	if (current_animation==move_left_index){
		animations[current_animation]=animations[current_animation]->next;
	}
	else{
		current_animation=move_left_index;
		direction='l';
	}
}

void Character::moveRight(pMap map){
	Physical::moveDown(map);
	if (current_animation==move_right_index){
		animations[current_animation]=animations[current_animation]->next;
	}
	else{
		current_animation=move_right_index;
		direction='r';
	}
}



//FUNZIONI COMBATTIMENTO

void Character::initiate_attack (){
	is_attacking=true;
	(equipaggiamento.arma)->initiate_attack(direction);
	switch (direction){
		case 'u':
			current_animation=move_up_index;
			attack_counter=attack_up_states;
			break;
		case 'd':
			current_animation=move_down_index;
			attack_counter=attack_down_states;
			break;
		case 'r':
			current_animation=move_right_index;
			attack_counter=attack_right_states;
			break;
		case 'l':
			current_animation=move_left_index;
			attack_counter=attack_left_states;
			break;
	}
}


int Character::calculate_damage(pCharacter c){
    int damage;
    damage=danno_fisico-(c->difesa_fisica/2)+danno_magico-(c->difesa_magica/2);
    if (damage>0)
        return (-(damage));
    else
        return 0;
}

void Character::changeCurrentHealth(int delta) {
	curHealth += delta;
}
/*
#pragma region AUSILIARIE_GENERICHE
	void Character::swapPositions(pCharacter this[], Coordinate a, Coordinate b) {
		pCharacter tmp = this[a.single()];
		this[a.single()] = this[b.single()];
		this[b.single()] = tmp;
	}
#pragma endregion AUSILIARIE_GENERICHE

*/