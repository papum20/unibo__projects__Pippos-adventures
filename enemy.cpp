#include "enemy.hpp"

Enemy::Enemy() {
    
}

Enemy::Enemy(int max_health, int max_stamina):Character (max_health, max_stamina){
    
}

/*void Enemy::update(pInanimate map[], pCharacter characters[]){
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

*/