#include "fire_spirit_hands.hpp"

Fire_spirit_hands::Fire_spirit_hands():Hands(){
    danno_fisico_iniziale=0;
    danno_magico_iniziale=Math::randomStep(20, 40, 5);

    move_up_index=fire_spirit_hands_up_index;
	move_up_index=fire_spirit_hands_down_index;
	move_left_index=fire_spirit_hands_left_index;
	move_right_index=fire_spirit_hands_right_index;

	attack_up_index=fire_spirit_hands_attack_up_index;
	attack_down_index=fire_spirit_hands_attack_down_index;
	attack_left_index=fire_spirit_hands_attack_left_index;
	attack_right_index=fire_spirit_hands_attack_right_index;

    animations[move_up_index]= new Animation (fire_spirit_hands_up, Coordinate(fire_spirit_hands_width, fire_spirit_hands_height), fire_spirit_hands_movement_states);
    animations[move_down_index]= new Animation (fire_spirit_hands_down, Coordinate(fire_spirit_hands_width, fire_spirit_hands_height), fire_spirit_hands_movement_states);
    animations[move_left_index]= new Animation (fire_spirit_hands_left, Coordinate(fire_spirit_hands_width, fire_spirit_hands_height), fire_spirit_hands_movement_states);
    animations[move_right_index]= new Animation (fire_spirit_hands_right, Coordinate(fire_spirit_hands_width, fire_spirit_hands_height), fire_spirit_hands_movement_states);

    animations[attack_up_index]= new Animation (fire_spirit_hands_attack_up, Coordinate(fire_spirit_hands_width, fire_spirit_hands_height), fire_spirit_hands_attack_states);
    animations[attack_down_index]= new Animation (fire_spirit_hands_attack_down, Coordinate(fire_spirit_hands_width, fire_spirit_hands_height), fire_spirit_hands_attack_states);
    animations[attack_left_index]= new Animation (fire_spirit_hands_attack_left, Coordinate(fire_spirit_hands_width, fire_spirit_hands_height), fire_spirit_hands_attack_states);
    animations[attack_right_index]= new Animation (fire_spirit_hands_attack_right, Coordinate(fire_spirit_hands_width, fire_spirit_hands_height), fire_spirit_hands_attack_states);
    
    is_melee=false;
    owner_id=ID_ENEMY_S;

    horizontal_attack_states=fire_spirit_hands_attack_states;
    vertical_attack_states=fire_spirit_hands_attack_states;
    projectile= new Fireball(danno_fisico, danno_magico, direction, owner_id);
}

/*pProjectile Fire_spirit_hands::shoot(){
    pFireball fireball= new Fireball(danno_fisico, danno_magico, direction, owner_id);
    return fireball;
}
*/