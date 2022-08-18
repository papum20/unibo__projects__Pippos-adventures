#include "player.hpp"

Player::Player():Character(p_max_health, p_max_stamina) {
	n_hearts=start_lifes;
	id=ID_PLAYER;
	animation[idle_index] = new Animation(idle, p_height, p_width, idle_states);
	
	animation[move_right_index] = new Animation(move_right, p_height, p_width, move_right_states);
	animation[move_left_index] = new Animation(move_left, p_height, p_width, move_left_states);
	animation[move_up_index] = new Animation(move_up, p_height, p_width, move_up_states);
	animation[move_down_index] = new Animation(move_down, p_height, p_width, move_down_states);

	animation[dash_up_index] = new Animation(dash_up, p_height, p_width, dash_up_states);
	animation[dash_down_index] = new Animation(dash_down, p_height, p_width, dash_down_states);
	animation[dash_left_index] = new Animation(dash_left, p_height, p_width, dash_left_states);
	animation[dash_right_index] = new Animation(dash_right, p_height, p_width, dash_right_states);
	
}

void Player::apply_equipment (){
	player.danno_fisico=(equipaggiamento->arma)->danno_fisico;
	player.danno_magico=(equipaggiamento->arma)->danno_magico;

	player.difesa_fisica=(equipaggiamento->scudo)->difesa_fisica+(equipaggiamento->armatura).difesa_fisica+(equipaggiamento->stivali).difesa_fisica;
	player.difesa_magica=(equipaggiamento->scudo)->difesa_magica+(equipaggiamento->armatura).difesa_magica+(equipaggiamento->collana).difesa_magica;
}

void Player::change_weapon(pWeapon w){
	(equipaggiamento->arma)=w;
	apply_equipment();
}

void Player::change_necklace(pNeckalce n){
	(equipaggiamento->collana)=n;
	apply_equipment();
}

void Player::change_shield (pShield s){
	(equipaggiamento->scudo)=s;
	apply_equipment();
}

void Player::change_armor (pArmatura a){
	(equipaggiamento->armatura)=a;
	apply_equipment();
}

void Player::change_boots (pBoots b){
	(equipaggiamento->stivali)=b;
	apply_equipment();
}


void Player::update(pInanimate map[], pCharacter characters[]){
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

void Player::collect_item(){
	Coordinate newcoord;
	newcoord=pos;
	if (direction=='u'){
		newcoord.y--;
		add_item(Room::checkItem(newcoord));
	}
	if (direction=='d'){
		newcoord.y++;
		add_item(Room::checkItem(newcoord));
	}
	if (direction=='l'){
		newcoord.x--;
		add_item(Room::checkItem(newcoord));
	}
	if (direction=='r'){
		newcoord.x++;
		add_item(Room::checkItem(newcoord));
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