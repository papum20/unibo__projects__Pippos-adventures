#include "enemy.hpp"


Enemy::Enemy(int max_health, int max_stamina, int p_g):Character (max_health, max_stamina){
    points_given=p_g;
}

void Enemy::update(pInanimate map[], pCharacter characters[]){
    if (is_attacking)
        if (animazione corrente è l ultima){
            calculate_damage();
            is_attacking=false;
        }
        else{
            //next animation
        }
    else{
        enemy_ia();
    }
}