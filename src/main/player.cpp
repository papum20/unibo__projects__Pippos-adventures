#include "main/player.hpp"
#include "main/map_handler.hpp"

Player::Player(pInputManager in, System_text* system_text):Character(p_max_health, p_max_stamina){
	text=system_text;
	size=Coordinate (p_width, p_depth);
	speed = SPEED_PLAYER;

	in_manager=in;

	n_hearts=start_hearts;
	n_keys = 0;
	id=ID_PLAYER;
	main_color = COLOR_PLAYER;

	used_door = NULL;

	animations[player_idle_index] = new Animation(idle, Coordinate(p_height, p_width), player_idle_states);
	
	animations[player_move_right_index] = new Animation(move_right, Coordinate(p_height, p_width), player_move_right_states);
	animations[player_move_left_index] = new Animation(move_left, Coordinate(p_height, p_width), player_move_left_states);
	animations[player_move_up_index] = new Animation(move_up, Coordinate(p_height, p_width), player_move_up_states);
	animations[player_move_down_index] = new Animation(move_down, Coordinate(p_height, p_width), player_move_down_states);

	animations_n = 5;


	idle_index=player_idle_index;
	move_right_index=player_move_right_index;
	move_left_index=player_move_left_index;
	move_up_index=player_move_up_index;
	move_down_index=player_move_down_index;
	points=0;

	artifacts[0]=new HealthPotion();
	artifacts[1]= new Life_elixir();
	weapons[0]= new sword();
	weapons[1]= new Arco();
	defensive_items[0] = new armor();
	weapons_n = 2;
	defensive_items_n =1;
	artifacts_n = 2;
	change_weapon(weapons[0]);
	change_armor(defensive_items[0]);
	

	
}

void Player::changeCurrentHealth(int delta){
	if (curHealth+delta>=maxHealth){
		curHealth=maxHealth;
	}
	else
		if (curHealth+delta<0){
			if (n_hearts>0){
				n_hearts--;
				text->insert_string(lose_heart);
				curHealth=p_max_health;
			}
			else
				curHealth=-1;
		}
		else
			curHealth=curHealth+delta;
}

void Player::update(pMap map){
	if (!updated){
		if (curHealth>0){
			if (is_attacking){
					if (!equipaggiamento.arma->check_frame()){
						next_animation();
						equipaggiamento.arma->next_animation();
					}
					else{
						if (!equipaggiamento.arma->is_melee)
							ranged_attack(map);
						else
							check_enemy_melee(map);
						is_attacking=false;
					}
			}
			else{
				equipaggiamento.arma->resetAttack();
				switch (direction){
							case 'u':
								current_animation=move_up_index;
								equipaggiamento.arma->current_animation=equipaggiamento.arma->move_up_index;
								break;
							case 'd':
								current_animation=move_down_index;
								equipaggiamento.arma->current_animation=equipaggiamento.arma->move_down_index;
								break;
							case 'l':
								current_animation=move_left_index;
								equipaggiamento.arma->current_animation=equipaggiamento.arma->move_left_index;
								break;
							case 'r':
								current_animation=move_right_index;
								equipaggiamento.arma->current_animation=equipaggiamento.arma->move_right_index;
								break;	
						}
				int input;
				input=in_manager->get_input();
				switch (input){
					case KEY_UP:{
						moveUp(map);
						break;
					}
					case KEY_DOWN:{
						moveDown(map);
						break;
					}	
					case KEY_LEFT:{
						moveLeft(map);
						break;
					}
					case KEY_RIGHT:{
						moveRight(map);
						break;
					}
					case 'c':{
						collect_item(map);
						break;
					}
					case 'v':{
						door_actions(map);
						break;
					}
					case ('w'):{
						direction='u';
						if (checkStamina())
							initiate_attack();
						break;
					}
					case ('a'):{
						direction='l';
						if (checkStamina())
							initiate_attack();
						break;
					}
					case ('d'):{
						direction='r';
						if (checkStamina())
							initiate_attack();
						break;
					}
					case ('s'):{
						direction='d';
						if (checkStamina())
							initiate_attack();
						break;
					}
				}
			}
			Character::update(map);		//azioni generali
		}
		else
			if (curHealth!=-1)
				changeCurrentHealth(-1);
	}
}

void Player::check_enemy_melee(pMap map){
	pCharacter defender=NULL;
    pPhysical objects[ROOM_AREA];
	Coordinate start;
	Coordinate end;
	switch (direction){
		case 'u':
			start=Coordinate (pos.x+(size.x-(equipaggiamento.arma)->vertical_size.x)/2, pos.y+size.y);
			end=Coordinate (Coordinate (start, (equipaggiamento.arma)->vertical_size), Coordinate (-1, -1));
			break;
		case 'd':
			start=Coordinate (pos.x+(size.x-(equipaggiamento.arma)->vertical_size.x)/2, pos.y-(equipaggiamento.arma)->vertical_size.y );
			end=Coordinate (Coordinate (start, (equipaggiamento.arma)->vertical_size), Coordinate (-1, -1));
			break;
		case 'l':
			start=Coordinate (pos.x-(equipaggiamento.arma)->horizontal_size.x, (pos.y+(size.y-equipaggiamento.arma->horizontal_size.y)/2));
			end=Coordinate (Coordinate (start, (equipaggiamento.arma)->horizontal_size), Coordinate (-1, -1));
			break;
		case 'r':
			start=Coordinate (pos.x+size.x, pos.y+(size.y-(equipaggiamento.arma)->horizontal_size.y)/2);
			end=Coordinate (Coordinate (start, (equipaggiamento.arma)->horizontal_size), Coordinate (-1, -1));
			break;
	}

	int dim=MapHandler::checkRectangle(map, objects, start, end);       
    
    if (dim>0){                                                            
        for (int i=0; i<dim; i++){
            if (objects[i]->getId()!=this->id && objects[i]->isCharacter()){         
                defender=MapHandler::checkCharacter(map, objects[i]->getPosition());       
                defender->changeCurrentHealth(calculate_damage(defender));
            }
        }
    }
}

bool Player::checkStamina(){
	if (curStamina-stamina_cost<0){
		text->insert_string(no_stamina);
		return false;
	}
	else
		return true;
}
void Player::destroyInstance(pMap map){
	for (int i=0; i<weapons_n; i++){
		weapons[i]->destroy(NULL);
	}
	for (int i=0; i<defensive_items_n; i++){
		defensive_items[i]->destroy(NULL);
	}
	Character::destroyInstance(map);
}

void Player::collect_item(pMap mappa){
	Coordinate newcoord;
	newcoord=pos;
	pChest chest;
	if (direction=='u'){			//calcolo la coordinata in cui cercare la chest in base all'orientamento del pg
		newcoord.y=newcoord.y+size.y;
	}
	if (direction=='d'){
		newcoord.y--;
	}
	if (direction=='l'){
		newcoord.x--;
	}
	if (direction=='r'){
		newcoord.x=newcoord.x+size.x;
	}
	chest=MapHandler::checkChest(mappa, newcoord);				//cerco la chest
	if(chest != NULL) {
		switch (chest->type){						//in base al tipo contenuto nella chest richiedo l'oggetto contenuto
			case 'w':
				add_item(chest->open_w());			//aggiungo l'arma all'inventario
				break;
			case 'a':
				add_item(chest->open_a());			//aggiungo l'artefatto all'inventario
				break;
			case 'd':
				add_item(chest->open_d());			//aggiungo l'item difensivo all'inventario
				break;
			case 'k':
				n_keys++;
				break;
		}
		chest->destroy(mappa);
	}
}

void Player::add_item(pWeapon w){
	if (weapons_n<(W_NUMBER-1)){
		weapons[weapons_n]=new Weapon();
		weapons[weapons_n]->copyWeapon(*w);
		weapons_n++;
		text->insert_string(collect_weapon);
	}
	else
		text->insert_string(no_weapon);
}

void Player::add_item (pItem_def i){
	if (defensive_items_n<(DEF_NUMBER-1)){
		defensive_items[defensive_items_n]=new item_difensivo();
		defensive_items[defensive_items_n]->copyItemDifensivo(*i);
		defensive_items_n++;
		text->insert_string(collect_item_difensive);
	}
	else
		text->insert_string(no_item_difensive);
}

void Player::add_item (pArtifact a){
	if (artifacts_n<(MAX_ARTIFACTS-1)){
		artifacts[artifacts_n]=new Artifact();
		artifacts[artifacts_n]->copyArtifact(*a);
		artifacts_n++;
		text->insert_string(collect_artifact);
	}
	else
		text->insert_string(no_artifacts);
}

void Player::modify_lifes (int delta){
	if (n_hearts<max_hearts)
		n_hearts=n_hearts+delta;
}

int Player::getPoints(){
	return points;
}

void Player::change_points(int delta){
    points+=delta;
}

void Player::door_actions(pMap map){
	Coordinate newcoord;
	newcoord=pos;
	if (direction=='u'){		
		newcoord.y=newcoord.y+size.y;
	}
	if (direction=='d'){
		newcoord.y--;
	}
	if (direction=='l'){
		newcoord.x--;
	}
	if (direction=='r'){
		newcoord.x=newcoord.x+size.x;
	}
	used_door=MapHandler::checkDoor(map, newcoord);
	if (used_door != NULL && used_door->isLocked()){
		if (n_keys>0){
			text->insert_string(door_unlocked);
			n_keys--;
		}
		else{
			used_door=NULL;
			text->insert_string(no_keys);
		}
	}
}

pDoor Player::usedDoor() {
	return used_door;
}

void Player::useDoor() {
	used_door = NULL;
}




int Player::getInventory(pItem inventory[n_max_inventory_objects]) {
	for(int i = 0; i < weapons_n; i++) inventory[i] = weapons[i];
	for(int i = 0; i < artifacts_n; i++) inventory[i + weapons_n] = artifacts[i];
	for(int i = 0; i < defensive_items_n; i++) inventory[i + weapons_n + artifacts_n] = defensive_items[i];
	return weapons_n + artifacts_n + defensive_items_n;
}
void Player::removeItem(pItem item) {
	bool found = false;
	int i = 0;
	while(!found && i < weapons_n) {
		if(item == weapons[i]) found = true;
		else i++;
	}
	if(!found) {
		i = 0;
		while(!found && i < artifacts_n) {
			if(item == artifacts[i]) found = true;
			else i++;
		}
	}
	if(!found) {
		i = 0;
		while(!found && i < defensive_items_n) {
			if(item == defensive_items[i]) found = true;
			else i++;
		}
	}

	if(found) {
		if(item->isWeapon()) {
			weapons[i] = weapons[weapons_n - 1];
			weapons_n--;
		} else if(item->isArtifact()) {
			artifacts[i] = artifacts[artifacts_n - 1];
			artifacts_n--;
		} else if(item->isItemDifensivo()) {
			defensive_items[i] = defensive_items[defensive_items_n- 1];
			defensive_items_n--;
		}
		item->destroy(NULL);
	}
}
