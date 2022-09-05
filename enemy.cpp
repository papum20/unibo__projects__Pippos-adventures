#include "enemy.hpp"
#include "map_handler.hpp"

Enemy::Enemy(pCharacter p):Character() {
    player=p;
	weapons_n=0;
	defensive_items_n=0;
	curHealth=maxHealth;
	maxStamina=enemy_stamina;
	curStamina=maxStamina;
}

/*Enemy::Enemy(int max_health, int max_stamina, int p_g, pCharacter p):Character (max_health, max_stamina){
    points_given=p_g;
    player=p;
}
*/

void Enemy::copyEnemy(Enemy B) {
	points_given = B.points_given;
    copyCharacter(B);
}

void Enemy::update(pMap map){
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
        if (equipaggiamento.arma->is_melee)
            meleeIA(map);
        else
            rangedIA(map);
    }

    Character::update(map);
}

/*

void Enemy::meleeIA(pMap map){
    Coordinate path[ROOM_AREA];
	Physical *obj[ROOM_AREA];
	int player_distance;
	int objects_in_view;
	player_distance=MapHandler::shortestPath(map, path, pos, player->getPosition(), player);		
	objects_in_view=MapHandler::vision(map, obj, pos, 10);

	if (player->findInArray(obj, objects_in_view) && player_distance<5){					//se il player è in vista e la distanza è minore di 5
		if (player_distance>1){																
			Coordinate step;
			step=path[0];
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
		else{ 																				//altrimenti lo attacco
			if (si trova a destra){
				direction='r';
			}
			if (si trova a sinistra){
				direction='l';
			}
			if (si trova su){
				direction='u';
			}
			if (si trova in basso){
				direction='d';
			}
			initiate_attack();
		
		}
	}

}

void Enemy::rangedIA(pMap map){
	Physical *obj[ROOM_AREA];
	int objects_in_view;	
	objects_in_view=MapHandler::vision(map, obj, pos, 10);
	if (player->findInArray(obj, objects_in_view)){																//se il player è in vista
		if (Math::abs(player->getPosition().x-pos.x)<Math::abs(player->getPosition().y-pos.y)){						//se sono più vicini sull'asse delle x
			if (Math::abs(player->getPosition().x-pos.x)<((equipaggiamento.arma)->projectile)->vertical_size.x){	//se la larghezza del proiettile>=distanza sulle x
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
			if (Math::abs(player->getPosition().y-pos.y)<((equipaggiamento.arma)->projectile)->horizontal_size.y){		//se l'altezza del proiettile>=distanza sulle y
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
}

*/