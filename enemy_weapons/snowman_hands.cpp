#include "snowman_hands.hpp"

Snowman_hands::Snowman_hands(int d_f, int d_m, const char rar[], const char n[], const char desc[]):Hands(d_f, d_m, rar, n, desc){
    move_up_index=snowman_hands_up_index;
	move_up_index=snowman_hands_down_index;
	move_left_index=snowman_hands_left_index;
	move_right_index=snowman_hands_right_index;

	attack_up_index=snowman_hands_attack_up_index;
	attack_down_index=snowman_hands_attack_down_index;
	attack_left_index=snowman_hands_attack_left_index;
	attack_right_index=snowman_hands_attack_right_index;

    animations[move_up_index]= new Animation (snowman_hands_up, snowman_hands_width, snowman_hands_height, snowman_hands_movement_states);
    animations[move_down_index]= new Animation (snowman_hands_down, snowman_hands_width, snowman_hands_height, snowman_hands_movement_states);
    animations[move_left_index]= new Animation (snowman_hands_left, snowman_hands_width, snowman_hands_height, snowman_hands_movement_states);
    animations[move_right_index]= new Animation (snowman_hands_right, snowman_hands_width, snowman_hands_height, snowman_hands_movement_states);

    animations[attack_up_index]= new Animation (snowman_hands_attack_up, snowman_hands_width, snowman_hands_height, snowman_hands_attack_states);
    animations[attack_down_index]= new Animation (snowman_hands_attack_down, snowman_hands_width, snowman_hands_height, snowman_hands_attack_states);
    animations[attack_left_index]= new Animation (snowman_hands_attack_left, snowman_hands_width, snowman_hands_height, snowman_hands_attack_states);
    animations[attack_right_index]= new Animation (snowman_hands_attack_right, snowman_hands_width, snowman_hands_height, snowman_hands_attack_states);
}