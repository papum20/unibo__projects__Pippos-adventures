#include "snowman_hands.hpp"

Snowman_hands::Snowman_hands():Hands(){
    danno_fisico_iniziale=0;
    danno_magico_iniziale=Math::randomStep(30, 60, 5);

    move_up_index=snowman_hands_up_index;
	move_up_index=snowman_hands_down_index;
	move_left_index=snowman_hands_left_index;
	move_right_index=snowman_hands_right_index;

	attack_up_index=snowman_hands_attack_up_index;
	attack_down_index=snowman_hands_attack_down_index;
	attack_left_index=snowman_hands_attack_left_index;
	attack_right_index=snowman_hands_attack_right_index;

    animations[move_up_index]= new Animation (snowman_hands_up, Coordinate(snowman_hands_width, snowman_hands_height), snowman_hands_movement_states);
    animations[move_down_index]= new Animation (snowman_hands_down, Coordinate(snowman_hands_width, snowman_hands_height), snowman_hands_movement_states);
    animations[move_left_index]= new Animation (snowman_hands_left, Coordinate(snowman_hands_width, snowman_hands_height), snowman_hands_movement_states);
    animations[move_right_index]= new Animation (snowman_hands_right, Coordinate(snowman_hands_width, snowman_hands_height), snowman_hands_movement_states);

    animations[attack_up_index]= new Animation (snowman_hands_attack_up, Coordinate(snowman_hands_width, snowman_hands_height), snowman_hands_attack_states);
    animations[attack_down_index]= new Animation (snowman_hands_attack_down, Coordinate(snowman_hands_width, snowman_hands_height), snowman_hands_attack_states);
    animations[attack_left_index]= new Animation (snowman_hands_attack_left, Coordinate(snowman_hands_width, snowman_hands_height), snowman_hands_attack_states);
    animations[attack_right_index]= new Animation (snowman_hands_attack_right, Coordinate(snowman_hands_width, snowman_hands_height), snowman_hands_attack_states);

    is_melee=false;
    owner_id=ID_ENEMY_S;

    horizontal_attack_states=snowman_hands_attack_states;
    vertical_attack_states=snowman_hands_attack_states;

    projectile= new Snowball(danno_fisico, danno_magico, direction, owner_id);
}

/*pProjectile Snowman_hands::shoot(){
    pSnowball snowball=new Snowball(danno_fisico, danno_magico, direction, owner_id);
    return snowball;
}*/