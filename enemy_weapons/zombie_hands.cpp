#include "zombie_hands.hpp"

Zombie_hands::Zombie_hands(int d_f, int d_m, const char rar[], const char n[], const char desc[]):Hands(d_f, d_m, rar, n, desc){
    move_up_index=zombie_hands_up_index;
	move_up_index=zombie_hands_down_index;
	move_left_index=zombie_hands_left_index;
	move_right_index=zombie_hands_right_index;

	attack_up_index=zombie_hands_attack_up_index;
	attack_down_index=zombie_hands_attack_down_index;
	attack_left_index=zombie_hands_attack_left_index;
	attack_right_index=zombie_hands_attack_right_index;

    animations[move_up_index]= new Animation (zombie_hands_up, zombie_hands_width, zombie_hands_height, zombie_hands_movement_states);
    animations[move_down_index]= new Animation (zombie_hands_down, zombie_hands_width, zombie_hands_height, zombie_hands_movement_states);
    animations[move_left_index]= new Animation (zombie_hands_left, zombie_hands_width, zombie_hands_height, zombie_hands_movement_states);
    animations[move_right_index]= new Animation (zombie_hands_right, zombie_hands_width, zombie_hands_height, zombie_hands_movement_states);

    animations[attack_up_index]= new Animation (zombie_hands_attack_up, zombie_hands_width, zombie_hands_height, zombie_hands_attack_states);
    animations[attack_down_index]= new Animation (zombie_hands_attack_down, zombie_hands_width, zombie_hands_height, zombie_hands_attack_states);
    animations[attack_left_index]= new Animation (zombie_hands_attack_left, zombie_hands_width, zombie_hands_height, zombie_hands_attack_states);
    animations[attack_right_index]= new Animation (zombie_hands_attack_right, zombie_hands_width, zombie_hands_height, zombie_hands_attack_states);

    is_melee=true;
}