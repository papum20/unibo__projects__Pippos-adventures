#include "enemy.hpp"
#include "map_handler.hpp"

Enemy::Enemy() : Character() {
	maxStamina=enemy_stamina;
	curStamina=maxStamina;
	id= ID_ENEMY_S;
	animations_n = 5;
	player_in_vision=false;
	player_found=false;
	main_color = COLOR_ENEMY;
	frames_passed=enemy_refreshing_rate;
	current_step=0;
	memorized_steps=0;
}

Enemy::Enemy(pCharacter p):Character() {
	player = p;

	maxStamina=enemy_stamina;
	curStamina=maxStamina;
	id= ID_ENEMY_S;
	animations_n = 5;
	player_in_vision=false;
	player_found=false;
	main_color = COLOR_ENEMY;
	frames_passed=enemy_refreshing_rate;
	current_step=0;
	memorized_steps=0;
}

int Enemy::getPoints(){
	return points_given;
}

void Enemy::destroyInstance(pMap map){
	if(equipaggiamento.arma != NULL) equipaggiamento.arma->destroy(NULL);
	if(equipaggiamento.armatura != NULL) equipaggiamento.armatura->destroy(NULL);
	if(equipaggiamento.elmo != NULL) equipaggiamento.elmo->destroy(NULL);
	if(equipaggiamento.stivali != NULL) equipaggiamento.stivali->destroy(NULL);
	if(equipaggiamento.collana != NULL) equipaggiamento.collana->destroy(NULL);
	if(equipaggiamento.scudo != NULL) equipaggiamento.scudo->destroy(NULL);
	Character::destroyInstance(map);
}

void Enemy::copyEnemy(Enemy B) {
	points_given = B.points_given;
	if(B.equipaggiamento.arma != NULL) {
		change_weapon(new Weapon());
		equipaggiamento.arma->copyWeapon(*B.equipaggiamento.arma);
	}
	if(B.equipaggiamento.elmo != NULL) {
		change_helm(new item_difensivo());
		equipaggiamento.elmo->copyItemDifensivo(*B.equipaggiamento.elmo);
	}
	if(B.equipaggiamento.collana != NULL) {
		change_necklace(new item_difensivo());
		equipaggiamento.collana->copyItemDifensivo(*B.equipaggiamento.collana);
	}
	if(B.equipaggiamento.scudo != NULL) {
		change_shield(new item_difensivo());
		equipaggiamento.scudo->copyItemDifensivo(*B.equipaggiamento.scudo);
	}
	if(B.equipaggiamento.stivali != NULL) {
		change_boots(new item_difensivo());
		equipaggiamento.stivali->copyItemDifensivo(*B.equipaggiamento.stivali);
	}
	if(B.equipaggiamento.armatura != NULL) {
		change_armor(new item_difensivo());
		equipaggiamento.armatura->copyItemDifensivo(*B.equipaggiamento.armatura);
	}
	current_step=0;
	animation_rate=FRAMES_PER_SECOND/ANIMATIONS_PER_SECOND;
    animation_counter=animation_rate;
	Character::copyCharacter(B);
}

void Enemy::update(pMap map){
	if(!updated){
		if (curHealth>0){	
			if (!is_attacking){
				if (equipaggiamento.arma->is_melee){
					meleeIA(map);
				}
				else{
					rangedIA(map);
				}
			}
			else{
				if (!equipaggiamento.arma->check_frame()){
					next_animation();
					equipaggiamento.arma->next_animation();
				}
				else{
					equipaggiamento.arma->resetAttack();
					if (!equipaggiamento.arma->is_melee)
						ranged_attack(map);
					else{
						check_enemy_melee(map);
						if (player_found){
							player->changeCurrentHealth(calculate_damage(player));
							player_found=false;
						}
					}
					is_attacking=false;
					switch (direction){
						case 'u':
							current_animation=move_up_index;
							equipaggiamento.arma->current_animation=equipaggiamento.arma->move_up_index;
							if (!equipaggiamento.arma->is_melee)
								if (player->getPosition().x>pos.x)
									moveRight(map);
								else
									moveLeft(map);
							break;
						case 'd':
							current_animation=move_down_index;
							equipaggiamento.arma->current_animation=equipaggiamento.arma->move_down_index;
							if (!equipaggiamento.arma->is_melee)
								if (player->getPosition().x>pos.x)
									moveRight(map);
								else
									moveLeft(map);
							break;
						case 'l':
							current_animation=move_left_index;
							equipaggiamento.arma->current_animation=equipaggiamento.arma->move_left_index;
							if (!equipaggiamento.arma->is_melee)
								if (player->getPosition().y>pos.y)
									moveUp(map);
								else
									moveDown(map);
						case 'r':
							current_animation=move_right_index;
							equipaggiamento.arma->current_animation=equipaggiamento.arma->move_right_index;
							if (!equipaggiamento.arma->is_melee)
								if (player->getPosition().y>pos.y)
									moveUp(map);
								else
									moveDown(map);
							break;	
					}
				}
			}
			Character::update(map);
		}
		else{
			player->change_points(points_given);
			destroy(map);
		}
	}
}

void Enemy::check_enemy_melee(pMap map){
	Coordinate start;
	Coordinate end;
	
	//setto le coordinate per cercare in alto
	start=Coordinate (pos.x+(size.x-(equipaggiamento.arma)->vertical_size.x)/2, pos.y+size.y);
	end=Coordinate (Coordinate (start, (equipaggiamento.arma)->vertical_size), Coordinate (-1, -1));
	if (MapHandler::findRectangle(map, player, start, end)){
		direction='u';
		player_found=true;
	}
	//Basso
	if (!player_found){
		start=Coordinate (pos.x+(size.x-(equipaggiamento.arma)->vertical_size.x)/2, pos.y-(equipaggiamento.arma)->vertical_size.y );
		end=Coordinate (Coordinate (start, (equipaggiamento.arma)->vertical_size), Coordinate (-1, -1));
		if (MapHandler::findRectangle(map, player, start, end)){
			direction='d';
			player_found=true;
		}
	}
	//Sinistra
	if (!player_found){
		start=Coordinate (pos.x-(equipaggiamento.arma)->horizontal_size.x, pos.y+(size.y-(equipaggiamento.arma)->horizontal_size.y)/2);
		end=Coordinate (Coordinate (start, (equipaggiamento.arma)->horizontal_size), Coordinate (-1, -1));
		if (MapHandler::findRectangle(map, player, start, end)){
			direction='l';
			player_found=true;
		}
	}
	//Destra
	if (!player_found){
		start=Coordinate (pos.x+size.x, pos.y+(size.y-(equipaggiamento.arma)->horizontal_size.y)/2);
		end=Coordinate (Coordinate (start, (equipaggiamento.arma)->horizontal_size), Coordinate (-1, -1));
		if (MapHandler::findRectangle(map, player, start, end)){
			direction='r';
			player_found=true;
		}
	}
}


void Enemy::meleeIA(pMap map){
	WINDOW *w = newwin(10,10,10,1);
	box(w,0,0);
	mvwaddch(w,1,1,)
	check_enemy_melee(map);
	if (player_found){
		initiate_attack();
		player_found=false;
	}
	else{
		if (frames_passed<enemy_refreshing_rate){
			frames_passed++;
			if (player_in_vision && current_step<memorized_steps){
				make_step(map);
			}
		}
		else{
			frames_passed=0;
			//Physical *obj[ROOM_AREA];
			//Physical *obj2[ROOM_AREA];
			//int objects_in_view;
			//int objects_in_view2;
			//objects_in_view=MapHandler::vision(map, obj, pos, enemy_vision);
			//objects_in_view2=MapHandler::vision(map, obj2, Coordinate(pos,size.times(.5,.5)), enemy_vision);
			//if (player->findInArray(obj, objects_in_view) || player->findInArray(obj2, objects_in_view2)){
			bool b = MapHandler::visionLine_check(map, Coordinate(pos,size.times(.5,.5)), Coordinate(player->getPosition(), player->getSize().times(.5, .5)), enemy_vision);
			if (b){
				player_in_vision=true;
				int player_distance;
				Coordinate path[ROOM_AREA];
				player_distance=MapHandler::shortestPath_physical(map, path, this, player, 1, 1);
				if (player_distance>=max_steps){
					memorized_steps=max_steps;
					for (int i=0; i<memorized_steps; i++){
						memorized_path[i]=path[i];
					}
				}
				else{
					memorized_steps=player_distance;
					for (int i=0; i<memorized_steps; i++){
						memorized_path[i]=path[i];
					}
				}
				current_step=0;
				make_step(map);
			}
			else
				player_in_vision=false;

		}
	}
}

void Enemy::make_step(pMap map){
	if (current_step<max_steps){
		if (memorized_path[current_step].x==pos.intx()){																//se è maggiore di uno mi muovo nella sua direzione
			if (memorized_path[current_step].y>pos.inty())
				moveUp(map);
			else
				moveDown(map);
			}	
		else{																		
			if (memorized_path[current_step].x>pos.intx())
				moveRight(map);
			else
				moveLeft(map);
		}
		current_step++;
	}
}

void Enemy::rangedIA(pMap map){
	//Physical *obj[ROOM_AREA];
	//Physical *obj2[ROOM_AREA];
	//int objects_in_view;
	//int objects_in_view2;
	//objects_in_view=MapHandler::vision(map, obj, pos, enemy_vision);
	//objects_in_view2=MapHandler::vision(map, obj2, Coordinate(pos,size.times(.5,.5)), enemy_vision);
	//if ( (player->findInArray(obj, objects_in_view) || player->findInArray(obj2, objects_in_view2) ) && inRange()){
	bool b = MapHandler::visionLine_check(map, Coordinate(pos,size.times(.5,.5)), Coordinate(player->getPosition(), player->getSize().times(.5, .5)), enemy_vision);
	if ( b && inRange()){
		initiate_attack();
	}
	else{
		if (frames_passed<enemy_refreshing_rate){
			frames_passed++;
			if (player_in_vision && current_step<memorized_steps){
				make_step(map);
			}
		}
		else{
			frames_passed=0;
			//if (player->findInArray(obj, objects_in_view) || player->findInArray(obj2, objects_in_view2)){
			if (b){
				player_in_vision=true;
				int player_distance;
				Coordinate path[ROOM_AREA];
				player_distance=MapHandler::shortestPath_physical(map, path, this, player, 1, 1);
				if (player_distance>=max_steps){
					memorized_steps=max_steps;
					for (int i=0; i<memorized_steps; i++){
						memorized_path[i]=path[i];
					}
				}
				else{
					memorized_steps=player_distance;
					for (int i=0; i<memorized_steps; i++){
						memorized_path[i]=path[i];
					}
				}
				current_step=0;
				make_step(map);
			}
			else
				player_in_vision=false;
		}
	}
}


bool Enemy::inRange(){
	if (player->getPosition().x>=pos.x && player->getPosition().x<pos.x+size.x && Math::abs(pos.y-player->getPosition().y)<enemy_range/2){
		if (player->getPosition().y<pos.y){
			direction='d';
		}
		else{
			direction='u';
		}
		return true;
	}
	if (player->getPosition().y>=pos.y && player->getPosition().y<pos.y+size.y && Math::abs(pos.x-player->getPosition().x)<enemy_range/2){
		if (player->getPosition().x<pos.x){
			direction='l';
		}
		else{
			direction='r';
		}
		return true;
	}
	return false;
}