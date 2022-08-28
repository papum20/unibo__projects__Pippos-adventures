#include "fire_spirit_hands.hpp"

Fire_spirit_hands::Fire_spirit_hands():Hands(){
    move_up_index=fire_spirit_hands_up_index;
	move_up_index=fire_spirit_hands_down_index;
	move_left_index=fire_spirit_hands_left_index;
	move_right_index=fire_spirit_hands_right_index;

	attack_up_index=fire_spirit_hands_attack_up_index;
	attack_down_index=fire_spirit_hands_attack_down_index;
	attack_left_index=fire_spirit_hands_attack_left_index;
	attack_right_index=fire_spirit_hands_attack_right_index;

    animations[move_up_index]= new Animation (fire_spirit_hands_up, fire_spirit_hands_width, fire_spirit_hands_height, fire_spirit_hands_movement_states);
    animations[move_down_index]= new Animation (fire_spirit_hands_down, fire_spirit_hands_width, fire_spirit_hands_height, fire_spirit_hands_movement_states);
    animations[move_left_index]= new Animation (fire_spirit_hands_left, fire_spirit_hands_width, fire_spirit_hands_height, fire_spirit_hands_movement_states);
    animations[move_right_index]= new Animation (fire_spirit_hands_right, fire_spirit_hands_width, fire_spirit_hands_height, fire_spirit_hands_movement_states);

    animations[attack_up_index]= new Animation (fire_spirit_hands_attack_up, fire_spirit_hands_width, fire_spirit_hands_height, fire_spirit_hands_attack_states);
    animations[attack_down_index]= new Animation (fire_spirit_hands_attack_down, fire_spirit_hands_width, fire_spirit_hands_height, fire_spirit_hands_attack_states);
    animations[attack_left_index]= new Animation (fire_spirit_hands_attack_left, fire_spirit_hands_width, fire_spirit_hands_height, fire_spirit_hands_attack_states);
    animations[attack_right_index]= new Animation (fire_spirit_hands_attack_right, fire_spirit_hands_width, fire_spirit_hands_height, fire_spirit_hands_attack_states);
}