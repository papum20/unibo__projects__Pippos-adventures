#include "enemy.hpp"

Enemy::Enemy() {
    
}

Enemy::Enemy(int max_health, int max_stamina, int p_g):Character (max_health, max_stamina){
    points_given=p_g;
}

void Enemy::copyEnemy(Enemy B) {
	points_given = B.points_given;
    copyCharacter(B);
}

void Enemy::update(pMap map){
    if (is_attacking)
        if (animations[current_animation]->isLastFrame()){
            //calculate_damage();
            is_attacking=false;
        }
        else{
            //next animation
        }
    else{
        //enemy_ia();
    }
}