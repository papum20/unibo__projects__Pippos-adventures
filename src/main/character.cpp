#include "main/character.hpp"
#include "main/map_handler.hpp"

Character::Character() : Alive() {
	is_attacking=false;
	initialize_equipment();
}

Character::Character(int maxH, int maxS) : Alive(maxH, maxS) {
	is_attacking=false;
	initialize_equipment();
}

void Character::destroyInstance(pMap map){
	Physical::destroyInstance(map);
}

void Character::initialize_equipment(){
	equipaggiamento.arma=NULL;
	equipaggiamento.collana=NULL;
	equipaggiamento.armatura=NULL;
	equipaggiamento.scudo=NULL;
	equipaggiamento.stivali=NULL;
	equipaggiamento.elmo=NULL;
}

void Character::change_helm(pItem_def h){
	if (equipaggiamento.elmo!=NULL){
		(equipaggiamento.elmo)->is_equipped=false;
		(equipaggiamento.elmo)=h;
		(equipaggiamento.elmo)->is_equipped=true;
	}
	else{
		(equipaggiamento.elmo)=h;
		(equipaggiamento.elmo)->is_equipped=true;
	}
	apply_equipment();
}
void Character::change_weapon(pWeapon w){
	if (equipaggiamento.arma!=NULL){
		(equipaggiamento.arma)->is_equipped=false;
		(equipaggiamento.arma)=w;
		(equipaggiamento.arma)->is_equipped=true;
	}
	else{
		(equipaggiamento.arma)=w;
		(equipaggiamento.arma)->is_equipped=true;
	}
	apply_equipment();
}

void Character::change_necklace(pItem_def n){
	if (equipaggiamento.collana!=NULL){
		(equipaggiamento.collana)->is_equipped=false;
		(equipaggiamento.collana)=n;
		(equipaggiamento.collana)->is_equipped=true;
	}
	else{
		(equipaggiamento.collana)=n;
		(equipaggiamento.collana)->is_equipped=true;
	}
	apply_equipment();
}

void Character::change_shield (pItem_def s){
	if (equipaggiamento.scudo!=NULL){
		(equipaggiamento.scudo)->is_equipped=false;
		(equipaggiamento.scudo)=s;
		(equipaggiamento.scudo)->is_equipped=true;
	}
	else{
		(equipaggiamento.scudo)=s;
		(equipaggiamento.scudo)->is_equipped=true;
	}
	apply_equipment();
}

void Character::change_armor(pItem_def a){
	if (equipaggiamento.armatura!=NULL){
		(equipaggiamento.armatura)->is_equipped=false;
		(equipaggiamento.armatura)=a;
		(equipaggiamento.armatura)->is_equipped=true;
	}
	else{
		(equipaggiamento.armatura)=a;
		(equipaggiamento.armatura)->is_equipped=true;
	}
	apply_equipment();
}

void Character::change_boots (pItem_def b){
	if (equipaggiamento.stivali!=NULL){
		(equipaggiamento.stivali)->is_equipped=false;
		(equipaggiamento.stivali)=b;
		(equipaggiamento.stivali)->is_equipped=true;
	}
	else{
		(equipaggiamento.stivali)=b;
		(equipaggiamento.stivali)->is_equipped=true;
	}
	apply_equipment();
}

void Character::copyCharacter(Character B) {
	is_attacking = B.is_attacking;
	attack_counter=B.attack_counter;
	attacking_states=B.attacking_states;

	attack_up_states=B.attack_up_states;
	attack_down_states=B.attack_down_states;
	attack_right_states=B.attack_right_states;
	attack_left_states=B.attack_left_states;

	danno_fisico=B.danno_fisico;
	danno_magico=B.danno_magico;

	copyAlive(B);
}

void Character::update(pMap map) {
	Physical::update(map);
}

void Character::drawAtPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate win_size, Coordinate pos) {
	if(!drawn) {
		Animation a_weapon = equipaggiamento.arma->getCurrentAnimation();											//arma
		Coordinate draw_start = Coordinate(pos, equipaggiamento.arma->getOffset().negative());						//inizio disegno (con l'arma), sulla mappa
		Coordinate draw_end = Coordinate(draw_start, a_weapon.size);												//fine il disegno
		Coordinate character_start = pos, character_end = Coordinate(character_start, getCurrentAnimation().size);	//inizio e fine disegno del character
		Coordinate win_end = Coordinate(win_start, win_size);														//fine finestra

		Coordinate local = Coordinate(COORDINATE_ZERO, ANIMATION_SIZE, COORDINATE_ZERO, a_weapon.size);	//coordinata relativa all'animazione, all'interno di essa
		do {
			Coordinate global = Coordinate(Coordinate(local, draw_start), win_start, win_end);			//coordinata globale di local, sulla mappa
			if(global.inOwnBounds()) {																	//se il punto è interno alla finestra da disegnare
				if(equipaggiamento.arma->animationMask(local)){											//se c'è l'arma: copre qualsiasi cosa
					scr[global.rel_int_y()][global.rel_int_x()].edit(a_weapon.at(local), equipaggiamento.arma->get_MainColor(), -1, A_BOLD);
				}
				else if(global.inBounds(character_start, character_end)) {								//altrimenti, se c'è il character, disegna il character
					Coordinate local_character = Coordinate(global, character_start.negative());
					if(animationMask(local_character)) scr[global.rel_int_y()][global.rel_int_x()].edit(getCurrentAnimation().at(local_character), main_color, -1, A_BOLD);
				}
			}
			local.next();
		} while(!local.equals(COORDINATE_ZERO));

		drawn = true;
	}
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
		difesa_fisica=difesa_fisica+(equipaggiamento.elmo)->difesa_fisica;
	}
}

//FUNZIONI MOVIMENTO

void Character::moveUp(pMap map){
	if (curStamina+stamina_gain>maxStamina)
		curStamina=maxStamina;
	else
		curStamina+=stamina_gain;
	if (current_animation==move_up_index){
		next_animation();
		if (equipaggiamento.arma!=NULL)
			equipaggiamento.arma->next_animation();
	}
	else{
		current_animation=move_up_index;
		equipaggiamento.arma->current_animation=equipaggiamento.arma->move_up_index;
		direction='u';
		equipaggiamento.arma->direction=direction;
	}
	Animate::move(map);
}

void Character::moveDown(pMap map){
	if (curStamina+stamina_gain>maxStamina)
		curStamina=maxStamina;
	else
		curStamina+=stamina_gain;
	equipaggiamento.arma->resetAnimation();
	if (current_animation==move_down_index){
		next_animation();
		if (equipaggiamento.arma!=NULL)
			equipaggiamento.arma->next_animation();
	}
	else{
		current_animation=move_down_index;
		equipaggiamento.arma->current_animation=equipaggiamento.arma->move_down_index;
		direction='d';
		equipaggiamento.arma->direction=direction;
		resetAnimation();
		equipaggiamento.arma->resetAnimation();
	}
	Animate::move(map);
}

void Character::moveLeft(pMap map){
	if (curStamina+stamina_gain>maxStamina)
		curStamina=maxStamina;
	else
		curStamina+=stamina_gain;
	if (current_animation==move_left_index){
		next_animation();
		if (equipaggiamento.arma!=NULL)
			equipaggiamento.arma->next_animation();
	}
	else{
		current_animation=move_left_index;
		equipaggiamento.arma->current_animation=equipaggiamento.arma->move_left_index;
		direction='l';
		equipaggiamento.arma->direction=direction;
		resetAnimation();
		equipaggiamento.arma->resetAnimation();
	}
	Animate::move(map);
}

void Character::moveRight(pMap map){
	if (curStamina+stamina_gain>maxStamina)
		curStamina=maxStamina;
	else
		curStamina+=stamina_gain;
	if (current_animation==move_right_index){
		next_animation();
		if (equipaggiamento.arma!=NULL)
			equipaggiamento.arma->next_animation();
	}
	else{
		current_animation=move_right_index;
		equipaggiamento.arma->current_animation=equipaggiamento.arma->move_right_index;
		direction='r';
		equipaggiamento.arma->direction=direction;
		resetAnimation();
		equipaggiamento.arma->resetAnimation();
	}
	Animate::move(map);
}



//FUNZIONI COMBATTIMENTO
void Character::check_enemy_melee(pMap map){
	
}

void Character::change_points(int delta){
	
}

void Character::initiate_attack (){
	if (curStamina-stamina_cost>=0){
		curStamina=curStamina-stamina_cost;
		is_attacking=true;
		animation_counter=0;
		(equipaggiamento.arma)->initiate_attack(direction);
		switch (direction){
			case 'u':
				current_animation=move_up_index;
				break;
			case 'd':
				current_animation=move_down_index;
				break;
			case 'r':
				current_animation=move_right_index;
				break;
			case 'l':
				current_animation=move_left_index;
				break;
		}
	}
}

void Character::ranged_attack(pMap map){
	pProjectile proiettile;
	proiettile=(equipaggiamento.arma)->shoot();
	proiettile->setPosition(pos, size, direction);
	MapHandler::addProjectile(map, proiettile);
}


int Character::calculate_damage(pAlive c){
    int damage;
    damage=danno_fisico-(c->difesa_fisica/2)+danno_magico-(c->difesa_magica/2);
    if (damage>0)
        return (-(damage));
    else
        return 0;
}

equipment *Character::getEqipment() {
	return &equipaggiamento;
}

int Character::getPoints(){
	return -1;
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


