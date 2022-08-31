#include "player_rod.hpp"

Player_Rod::Player_Rod(int d_f, int d_m, const char rar[], const char n[], const char desc[]):Rod(d_f, d_m, rar, n, desc){
    move_up_index=player_rod_up_index;
	move_up_index=player_rod_down_index;
	move_left_index=player_rod_left_index;
	move_right_index=player_rod_right_index;

	attack_up_index=player_rod_attack_up_index;
	attack_down_index=player_rod_attack_down_index;
	attack_left_index=player_rod_attack_left_index;
	attack_right_index=player_rod_attack_right_index;

    animations[move_up_index]= new Animation (player_rod_up, player_rod_width, player_rod_height, player_rod_movement_states);
    animations[move_down_index]= new Animation (player_rod_down, player_rod_width, player_rod_height, player_rod_movement_states);
    animations[move_left_index]= new Animation (player_rod_left, player_rod_width, player_rod_height, player_rod_movement_states);
    animations[move_right_index]= new Animation (player_rod_right, player_rod_width, player_rod_height, player_rod_movement_states);

    animations[attack_up_index]= new Animation (player_rod_attack_up, player_rod_width, player_rod_height, player_rod_attack_states);
    animations[attack_down_index]= new Animation (player_rod_attack_down, player_rod_width, player_rod_height, player_rod_attack_states);
    animations[attack_left_index]= new Animation (player_rod_attack_left, player_rod_width, player_rod_height, player_rod_attack_states);
    animations[attack_right_index]= new Animation (player_rod_attack_right, player_rod_width, player_rod_height, player_rod_attack_states);

    is_melee=true;

}