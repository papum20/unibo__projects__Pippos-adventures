#include "player.hpp"

Player::Player():Character(p_max_health, p_max_stamina) {
	n_hearts=start_lifes;
	id=ID_PLAYER;
	animations[idle_index] = new Animation(idle, p_height, p_width, idle_states);
	
	animations[move_right_index] = new Animation(move_right, p_height, p_width, move_right_states);
	animations[move_left_index] = new Animation(move_left, p_height, p_width, move_left_states);
	animations[move_up_index] = new Animation(move_up, p_height, p_width, move_up_states);
	animations[move_down_index] = new Animation(move_down, p_height, p_width, move_down_states);

	animations[dash_up_index] = new Animation(dash_up, p_height, p_width, dash_up_states);
	animations[dash_down_index] = new Animation(dash_down, p_height, p_width, dash_down_states);
	animations[dash_left_index] = new Animation(dash_left, p_height, p_width, dash_left_states);
	animations[dash_right_index] = new Animation(dash_right, p_height, p_width, dash_right_states);

	/*animation[attack_up_index] = new Animation (attak_up, w_attack_height, w_attack_width, attack_up_states); 
	animation[attack_down_index] = new Animation (attak_up, w_attack_height, w_attack_width, attack_down_states);
	animation[attack_left_index] = new Animation (attak_up, w_attack_height, w_attack_width, attack_left_states);
	animation[attack_right_index] = new Animation (attak_up, w_attack_height, w_attack_width, attack_right_states);
	*/

	apply_equipment();

	//animation[indice che mi serve]

	//animation[move_right_index]=animation[move_right_index]->next
	//
	
}

void Player::change_weapon(pWeapon w){
	(equipaggiamento->arma).is_equipped=false;
	(equipaggiamento->arma)=w;
	(equipaggiamento->arma).is_equipped=true;
	apply_equipment();
}

void Player::change_necklace(pNeckalce n){
	(equipaggiamento->collana).is_equipped=false;
	(equipaggiamento->collana)=n;
	(equipaggiamento->collana).is_equipped=true;
	apply_equipment();
}

void Player::change_shield (pShield s){
	(equipaggiamento->scudo).is_equipped=false;
	(equipaggiamento->scudo)=s;
	(equipaggiamento->scudo).is_equipped=true;
	apply_equipment();
}

void Player::change_armor (pArmatura a){
	(equipaggiamento->armatura).is_equipped=false;
	(equipaggiamento->armatura)=a;
	(equipaggiamento->armatura).is_equipped=true;
	apply_equipment();
}

void Player::change_boots (pBoots b){
	(equipaggiamento->stivali).is_equipped=false;
	(equipaggiamento->stivali)=b;
	(equipaggiamento->stivali).is_equipped=true;
	apply_equipment();
}


void Player::update(pInanimate map[], pCharacter characters[], Room room){
	if (is_attacking)
		if (animazione corrente è l ultima){
			calculate_damage();
			is_attacking=false;
		}
		else{
			//avanti con l'animazione di attacco
		}
	else{
		int input=Input_manager::get_input(); 
		switch (input)
		{
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
			open_inventary();
			break;
		}
		case 'c':{
			collect_item();
		}
		case ctrl(w):{
			//iter animazione attacco alto
		}
		case ctrl(a):{
			//iter animazione attacco in sinistra
		}
		case ctrl(d):{
			//iter animazione attacco a destra
		}
		case ctrl(s):{
			//iter animazione attaco in basso
		}
		}
	}

}

void Player::collect_item(){
	Coordinate newcoord;
	newcoord=pos;
	if (direction=='u'){
		newcoord.y--;
		add_item(room.checkPosition(newcoord));
	}
	if (direction=='d'){
		newcoord.y++;
		add_item(room.checkPosition(newcoord));
	}
	if (direction=='l'){
		newcoord.x--;
		add_item(room.checkPosition(newcoord));
	}
	if (direction=='r'){
		newcoord.x++;
		add_item(room.checkPosition(newcoord));
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