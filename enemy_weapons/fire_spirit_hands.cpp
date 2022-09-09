#include "fire_spirit_hands.hpp"

Fire_spirit_hands::Fire_spirit_hands():Hands(){
    danno_fisico_iniziale=0;
    danno_magico_iniziale=Math::randomStep(30, 50, 10);
    apply_rarity();

    move_up_index=fire_spirit_hands_up_index;
	move_down_index=fire_spirit_hands_down_index;
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
    
    offset = Coordinate(fire_spirit_x_coordinate, fire_spirit_y_coordinate);

    is_melee=false;
    owner_id=ID_ENEMY_S;

    horizontal_attack_states=fire_spirit_hands_attack_states;
    vertical_attack_states=fire_spirit_hands_attack_states;
    projectile= Fireball(danno_fisico, danno_magico, direction, owner_id);
    current_animation=0;
}