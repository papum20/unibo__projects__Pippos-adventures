#include "player.hpp"

Player::Player(InputManager in, Menu m):Character(p_max_health, p_max_stamina) {
	in_manager=in;
	menu=m;

	n_hearts=start_lifes;
	id=ID_PLAYER;

	animations[player_idle_index] = new Animation(idle, p_height, p_width, player_idle_states);
	
	animations[player_move_right_index] = new Animation(move_right, p_height, p_width, player_move_right_states);
	animations[player_move_left_index] = new Animation(move_left, p_height, p_width, player_move_left_states);
	animations[player_move_up_index] = new Animation(move_up, p_height, p_width, player_move_up_states);
	animations[player_move_down_index] = new Animation(move_down, p_height, p_width, player_move_down_states);

	animations[player_dash_up_index] = new Animation(dash_up, p_height, p_width, player_dash_up_states);
	animations[player_dash_down_index] = new Animation(dash_down, p_height, p_width, player_dash_down_states);
	animations[player_dash_left_index] = new Animation(dash_left, p_height, p_width, player_dash_left_states);
	animations[player_dash_right_index] = new Animation(dash_right, p_height, p_width, player_dash_right_states);


	idle_index=player_idle_index;
	move_right_index=player_move_right_index;
	move_left_index=player_move_left_index;
	move_up_index=player_move_up_index;
	move_down_index=player_move_down_index;

	apply_equipment();
	
}

void Player::change_weapon(pWeapon w){
	(equipaggiamento.arma)->is_equipped=false;
	(equipaggiamento.arma)=w;
	(equipaggiamento.arma)->is_equipped=true;
	apply_equipment();
}

void Player::change_necklace(pNecklace n){
	(equipaggiamento.collana)->is_equipped=false;
	(equipaggiamento.collana)=n;
	(equipaggiamento.collana)->is_equipped=true;
	apply_equipment();
}

void Player::change_shield (pShield s){
	(equipaggiamento.scudo)->is_equipped=false;
	(equipaggiamento.scudo)=s;
	(equipaggiamento.scudo)->is_equipped=true;
	apply_equipment();
}

void Player::change_armor(pArmor a){
	(equipaggiamento.armatura)->is_equipped=false;
	(equipaggiamento.armatura)=a;
	(equipaggiamento.armatura)->is_equipped=true;
	apply_equipment();
}

void Player::change_boots (pBoots b){
	(equipaggiamento.stivali)->is_equipped=false;
	(equipaggiamento.stivali)=b;
	(equipaggiamento.stivali)->is_equipped=true;
	apply_equipment();
}


void Player::update(pInanimate map[], pCharacter characters[], pMap mappa){
	if (is_attacking)
		if (attack_counter==1){
			if ((equipaggiamento.arma)->is_melee)
				calculate_damage();
			is_attacking=false;
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
		}
		else{
			next_animation();
			equipaggiamento.arma->next_animation();
			attack_counter--;
		}
	else{
		int input;
		input=in_manager.get_input();
		switch (input){
			case KEY_UP:{
				moveUp(map, characters);
				break;
			}
			case KEY_DOWN:{
				moveDown(map, characters);
				break;
			}	
			case KEY_LEFT:{
				moveLeft(map, characters);
				break;
			}
			case KEY_RIGHT:{
				moveRight(map, characters);
				break;
			}
			case 'n':{
				menu.open();
				break;
			}
			case 'c':{
				collect_item(mappa);
			}
			case ctrl('w'):{
				direction='u';
				initiate_attack();
			}
			case ctrl('a'):{
				direction='l';
				initiate_attack();
				
			}
			case ctrl('d'):{
				direction='r';
				initiate_attack();
			}
			case ctrl('s'):{
				direction='d';
				initiate_attack();
			}
		}
	}

}

void Player::collect_item(pMap mappa){
	Coordinate newcoord;
	newcoord=pos;
	pChest chest;
	if (direction=='u'){			//calcolo la coordinata in cui cercare la chest in base all'orientamento del pg
		newcoord.y=newcoord.y-p_height;
	}
	if (direction=='d'){
		newcoord.y++;
	}
	if (direction=='l'){
		newcoord.x--;
	}
	if (direction=='r'){
		newcoord.x=newcoord.x+p_width;
	}
	chest=mappa->checkChest(newcoord);				//cerco la chest
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
	}
}

void Player::add_item(pWeapon w){
	if (curr_weapon<(W_NUMBER-1)){
		curr_weapon++;
		weapons[curr_weapon]=w;
	}
}

void Player::add_item (pItem_def i){
	if (last_def<(DEF_NUMBER-1)){
		last_def++;
		defensive_items[last_def]=i;
	}
}

void Player::add_item (pArtifact a){
	if (curr_artifact<(MAX_ARTIFACTS-1)){
		curr_artifact++;
		artifacts[curr_artifact]=a;
	}
}

void Player::modify_lifes (int delta){
	n_hearts=n_hearts+delta;
}


void Player::change_points(int delta){
    points+=delta;
}