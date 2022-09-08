#include "enemy.hpp"
#include "map_handler.hpp"

Enemy::Enemy() : Character() {
	weapons_n=0;
	defensive_items_n=0;
	maxStamina=enemy_stamina;
	curStamina=maxStamina;
	id= ID_ENEMY_S;
	animations_n = 5;

	main_color = COLOR_ENEMY;
}

Enemy::Enemy(pCharacter p):Character() {
    player=p;
	weapons_n=0;
	defensive_items_n=0;
	maxStamina=enemy_stamina;
	curStamina=maxStamina;
	id= ID_ENEMY_S;
	animations_n = 5;
	
	main_color = COLOR_ENEMY;
}

/*Enemy::Enemy(int max_health, int max_stamina, int p_g, pCharacter p):Character (max_health, max_stamina){
    points_given=p_g;
    player=p;
}
*/

int Enemy::getPoints(){
	return points_given;
}

void Enemy::destroy(pMap map){
	delete player;
	Character::destroy(map);
}

void Enemy::copyEnemy(Enemy B) {
	points_given = B.points_given;
    copyCharacter(B);
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
				if (equipaggiamento.arma->is_melee){
					if (attack_counter==1){
						check_enemy_melee(map);
						attack_counter=-1;
					}
					else
						attack_counter--;
				}
				if (!animations[current_animation]->isLastFrame()){
					next_animation();
					equipaggiamento.arma->next_animation();
				}
				else{
					if (!equipaggiamento.arma->is_melee)
						ranged_attack(map);
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
		}
		else
			destroy(map);
		Character::update(map);
	}
}

void Enemy::check_enemy_melee(pMap map){
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
            if (objects[i]->getId()==player->getId()){          
                player->changeCurrentHealth(calculate_damage(player));
            }
			break;
        }
    }
}


void Enemy::meleeIA(pMap map){
    Coordinate path[ROOM_AREA];
	Physical *obj[ROOM_AREA];
	Physical *obj2[ROOM_AREA];
	int player_distance;
	int objects_in_view;
	int objects_in_view2;
	player_distance=MapHandler::shortestPath_physical(map, path, this, player, 1, 1);		
	objects_in_view=MapHandler::vision(map, obj, pos, 30);
	objects_in_view2=MapHandler::vision(map, obj2, Coordinate(pos,size.times(.5,.5)), 30);

	//WINDOW *w = newwin(10,10,30,0);
	//box(w,0,0);
	//	mvwprintw(w,1,1,to_string(getPosition().x).c_str());
	//	mvwprintw(w,2,1,to_string(getPosition().y).c_str());
	//	for(int i = 0; i < 3; i++) {
	//		mvwprintw(w,3+i*2,1,to_string(path[i].x).c_str());
	//		mvwprintw(w,3+i*2+1,1,to_string(path[i].y).c_str());
	//	}
	//	wrefresh(w);
	/*for(int i = 0; i < player_distance; i++) {
		mvwprintw(w,1,1,to_string(path[i].x).c_str());
		mvwprintw(w,2,1,to_string(path[i].y).c_str());
		wgetch(w);
	}*/

	if ((player->findInArray(obj, objects_in_view) || player->findInArray(obj2, objects_in_view2)) && player_distance<20){					//se il player è in vista e la distanza è minore di 5
		if (player_distance>0){																
			Coordinate step;
			step=path[1];
			if (step.x==pos.x){																//se è maggiore di uno mi muovo nella sua direzione
				if (step.y>pos.y)
					moveUp(map);
				else
					moveDown(map);
			}	
			else{																		
				if (step.x>pos.x)
					moveRight(map);
				else
					moveLeft(map);
			}
		}
		else { 																				//altrimenti lo attacco
			if (pos.x<=player->getPosition().x && pos.x+size.x>player->getPosition().x)
				if (pos.y<player->getPosition().y)
					direction='u';
				else
					direction='d';
			else
				if (pos.x<player->getPosition().x)
					direction='r';
				else
					direction='l';
			initiate_attack();		
		}
	}

}

void Enemy::rangedIA(pMap map){
	Physical *obj[ROOM_AREA];
	int objects_in_view;	
	objects_in_view=MapHandler::vision(map, obj, pos, 20);
	Coordinate path[ROOM_AREA];
	int player_distance;
	player_distance=MapHandler::shortestPath_physical(map, path, this, player, 1, 1);
	if (player->findInArray(obj, objects_in_view)){																//se il player è in vista
		if (player_distance<10){	
			if (Math::abs(player->getPosition().x-pos.x)<Math::abs(player->getPosition().y-pos.y)){						//se sono più vicini sull'asse delle x
				if (Math::abs(player->getPosition().x-pos.x)<((equipaggiamento.arma)->projectile).vertical_size.x){	//se la larghezza del proiettile>=distanza sulle x
					if (player->getPosition().y>pos.y){																//mi direziono in base alla posizione
						direction='u';
					}
					else																							
						direction='d';
					initiate_attack();																				//inizio l'attacco
				}
				else{																							//se il proiettile non è sufficientemente largo, mi sposto
					if (player->getPosition().x>pos.x){															//in orizzontale, avvicinandomi
						moveRight(map);
					}
					else
						moveLeft(map);
				}
			}
			else{																										//se sono più vicini sulle y
				if (Math::abs(player->getPosition().y-pos.y)<((equipaggiamento.arma)->projectile).horizontal_size.y){		//se l'altezza del proiettile>=distanza sulle y
					if (player->getPosition().x>pos.x){														//mi direziono in base alla posizione
						direction='r';
					}
					else
						direction='l';
					initiate_attack();																		//inizio l'attacco
				}
				else{
					if (player->getPosition().y>pos.y){												//altrimenti mi sposto in verticale
						moveUp(map);
					}
					else
						moveDown(map);
				}
			}
		}
		else if (player_distance<15){
			Coordinate step;
			step=path[0];
			if (step.x==pos.x){																
				if (step.y>pos.y)
					moveUp(map);
				else
					moveDown(map);
			}	
			else{																		
				if (step.x>pos.x)
					moveRight(map);
				else
					moveLeft(map);
			}
		}
	}
}