#include "character.hpp"
#include "map_handler.hpp"


Character::Character() : Alive() {
	is_attacking=false;
	current_animation=idle_index;
}

Character::Character(int maxH, int maxS) : Alive(maxH, maxS) {
	is_attacking=false;
	current_animation=idle_index;
}
void Character::copyCharacter(Character B) {
	is_attacking = B.is_attacking;
	attack_counter=B.attack_counter;
	attacking_states=B.attacking_states;

	idle_index=B.idle_index;
	move_up_index=B.move_up_index;
	move_down_index=B.move_down_index;
	move_left_index=B.move_left_index;
	move_right_index=B.move_right_index;

	attack_up_states=B.attack_up_states;
	attack_down_states=B.attack_down_states;
	attack_right_states=B.attack_right_states;
	attack_left_states=B.attack_left_states;

	equipaggiamento=B.equipaggiamento;

	weapons_n=B.weapons_n;
	for(int i = 0; i < weapons_n;i++) weapons[i]=B.weapons[i];
	curr_weapon=B.curr_weapon;

	defensive_items_n=B.defensive_items_n;
	for(int i = 0; i < defensive_items_n;i++) defensive_items[i]=B.defensive_items[i];
	last_def=B.last_def;
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

		Coordinate local = Coordinate(0, 0, a_weapon.size);										//coordinata relativa all'animazione, all'interno di essa
		do {
			Coordinate global = Coordinate(Coordinate(local, draw_start), win_start, win_end);	//coordinata globale di local, sulla mappa
			if(global.inOwnBounds()) {															//se il punto è interno alla finestra da disegnare
				if(equipaggiamento.arma->animationMask(local))									//se c'è l'arma: copre qualsiasi cosa
					scr[global.rel_int_y()][global.rel_int_x()] = Cell(a_weapon.state[local.single()], equipaggiamento.arma->get_MainColor(), -1, -1);
				else if(global.inBounds(character_start, character_end)) {						//altrimenti, se c'è il character, disegna il character
					Coordinate local_character = Coordinate(global, character_start.negative());
					if(animationMask(local_character)) scr[global.rel_int_y()][global.rel_int_x()] = Cell(getCurrentAnimation().state[local_character.single()], main_color, -1, CELL_NO_ATTR);
				}
			}
		} while(!local.equals(draw_start));

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

void Character::check_enemy_melee(pMap map){
	pCharacter defender=NULL;
    pPhysical objects[ROOM_AREA];
	Coordinate start;
	Coordinate end;
	switch (direction){
		case 'u':
			start=Coordinate (pos.x+(equipaggiamento.arma)->delta_x_horizontal, pos.y+size.y);
			end=Coordinate (Coordinate (start, (equipaggiamento.arma)->vertical_size), Coordinate (-1, -1));
			break;
		case 'd':
			start=Coordinate ( pos.x+(equipaggiamento.arma)->delta_x_horizontal, pos.y-(equipaggiamento.arma)->vertical_size.y );
			end=Coordinate (Coordinate (start, (equipaggiamento.arma)->vertical_size), Coordinate (-1, -1));
			break;
		case 'l':
			start=Coordinate (pos.x-(equipaggiamento.arma)->horizontal_size.x, pos.y+(equipaggiamento.arma)->delta_y_vertical);
			end=Coordinate (Coordinate (start, (equipaggiamento.arma)->horizontal_size), Coordinate (-1, -1));
			break;
		case 'r':
			start=Coordinate (pos.x+size.x, pos.y+(equipaggiamento.arma)->delta_y_vertical);
			end=Coordinate (Coordinate (start, (equipaggiamento.arma)->horizontal_size), Coordinate (-1, -1));
			break;
	}

	int dim=MapHandler::checkRectangle(map, objects, start, end);       
    
    if (dim!=0){                                                            
        for (int i=0; i<dim; i++){
            if (objects[i]->getId()!=this->id && objects[i]->isCharacter()){         
                defender=MapHandler::checkCharacter(map, objects[i]->getPosition());       
                defender->changeCurrentHealth(calculate_damage(defender));    
            }
        }
    }

}
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
	Animate::moveDown(map);
	if (current_animation==move_up_index){
		animations[current_animation]=animations[current_animation]->next;
	}
	else{
		current_animation=move_up_index;
		direction='u';
	}
}

void Character::moveDown(pMap map){
	Animate::moveDown(map);
	if (current_animation==move_down_index){
		animations[current_animation]=animations[current_animation]->next;
	}
	else{
		current_animation=move_down_index;
		direction='d';
	}
}

void Character::moveLeft(pMap map){
	Animate::moveDown(map);
	if (current_animation==move_left_index){
		animations[current_animation]=animations[current_animation]->next;
	}
	else{
		current_animation=move_left_index;
		direction='l';
	}
}

void Character::moveRight(pMap map){
	Animate::moveDown(map);
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
			attacking_states=equipaggiamento.arma->vertical_attack_states;
			break;
		case 'd':
			current_animation=move_down_index;
			attacking_states=equipaggiamento.arma->vertical_attack_states;
			break;
		case 'r':
			current_animation=move_right_index;
			attacking_states=equipaggiamento.arma->horizontal_attack_states;
			break;
		case 'l':
			current_animation=move_left_index;
			attacking_states=equipaggiamento.arma->horizontal_attack_states;
			break;
	}
}

void Character::ranged_attack(pMap map){
	pProjectile proiettile;
	proiettile=(equipaggiamento.arma)->shoot();
	proiettile->setPosition(pos, size);
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
/*
#pragma region AUSILIARIE_GENERICHE
	void Character::swapPositions(pCharacter this[], Coordinate a, Coordinate b) {
		pCharacter tmp = this[a.single()];
		this[a.single()] = this[b.single()];
		this[b.single()] = tmp;
	}
#pragma endregion AUSILIARIE_GENERICHE

*/