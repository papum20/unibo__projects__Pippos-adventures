#include "player.hpp"
#include "map_handler.hpp"

Player::Player(pInputManager in):Character(p_max_health, p_max_stamina){
	in_manager=in;
	//menu=m;
	arma= new sword();
	armatura=new armor();
	collana=NULL;
	elmo=NULL;
	scudo=NULL;
	stivali=NULL;

	n_hearts=start_hearts;
	n_keys = 0;
	id=ID_PLAYER;
	main_color = COLOR_PLAYER;
	points = 0;

	used_door = NULL;

	animations[player_idle_index] = new Animation(idle, Coordinate(p_height, p_width), player_idle_states);
	
	animations[player_move_right_index] = new Animation(move_right, Coordinate(p_height, p_width), player_move_right_states);
	animations[player_move_left_index] = new Animation(move_left, Coordinate(p_height, p_width), player_move_left_states);
	animations[player_move_up_index] = new Animation(move_up, Coordinate(p_height, p_width), player_move_up_states);
	animations[player_move_down_index] = new Animation(move_down, Coordinate(p_height, p_width), player_move_down_states);

	//animations[player_dash_up_index] = new Animation(dash_up, Coordinate(p_height, p_width), player_dash_up_states);
	//animations[player_dash_down_index] = new Animation(dash_down, Coordinate(p_height, p_width), player_dash_down_states);
	//animations[player_dash_left_index] = new Animation(dash_left, Coordinate(p_height, p_width), player_dash_left_states);
	//animations[player_dash_right_index] = new Animation(dash_right, Coordinate(p_height, p_width), player_dash_right_states);


	idle_index=player_idle_index;
	move_right_index=player_move_right_index;
	move_left_index=player_move_left_index;
	move_up_index=player_move_up_index;
	move_down_index=player_move_down_index;
	points=0;
	change_weapon(arma);
	change_armor(armatura);
	size=Coordinate (p_width, p_depth);
	
}

void Player::changeCurrentHealth(int delta){
	if (curHealth+delta>=maxHealth){
		curHealth=maxHealth;
	}
	else
		if (curHealth+delta<0){
			if (n_hearts>0){
				n_hearts--;
				curHealth=p_max_health;
			}
			else
				destroy();
		}
		else
			curHealth=curHealth+delta;
}

void Player::update(pMap map){
	/*if (!updated){
		if (curHealth>0){
			if (is_attacking){
				if (!animations[current_animation]->isLastFrame()){
					if (attack_counter==1){
						if ((equipaggiamento.arma)->is_melee)
							check_enemy_melee(map);
						else{
							ranged_attack(map);
						}
					}
					next_animation();
					equipaggiamento.arma->next_animation();
					attack_counter--;
				}
				else{
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
			}
			else{
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
			Character::update(map);		//azioni generali
		}
		else
			destroy();
	}*/
}

void Player::check_enemy_melee(pMap map){
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
    
    if (dim>0){                                                            
        for (int i=0; i<dim; i++){
            if (objects[i]->getId()!=this->id && objects[i]->isCharacter()){         
                defender=MapHandler::checkCharacter(map, objects[i]->getPosition());       
                defender->changeCurrentHealth(calculate_damage(defender));
				if (defender->getHealth()==0)
					points=points+defender->getPoints();
            }
        }
    }
}

void Player::destroy(){
	delete used_door;
	for (int i=0; i<MAX_ARTIFACTS; i++)
		delete artifacts[i];
	delete in_manager;
	delete armatura;
	delete collana;
	delete elmo;
	delete scudo;
	delete stivali;
	delete arma;
	Character::destroy();
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
		weapons_n++;
	}
}

void Player::add_item (pItem_def i){
	if (last_def<(DEF_NUMBER-1)){
		last_def++;
		defensive_items[last_def]=i;
		defensive_items_n++;
	}
}

void Player::add_item (pArtifact a){
	if (curr_artifact<(MAX_ARTIFACTS-1)){
		curr_artifact++;
		artifacts[curr_artifact]=a;
		artifacts_n++;
	}
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
pDoor Player::usedDoor() {
	return used_door;
}
void Player::useDoor() {
	used_door = NULL;
}