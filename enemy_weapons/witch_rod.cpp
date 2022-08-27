#include "witch_rod.hpp"

Witch_Rod::Witch_Rod(int d_f, int d_m, const char rar[], const char n[], const char desc[]):Rod(d_f, d_m, rar, n, desc){
    move_up_index=witch_rod_up_index;
	move_up_index=witch_rod_down_index;
	move_left_index=witch_rod_left_index;
	move_right_index=witch_rod_right_index;

	attack_up_index=witch_rod_attack_up_index;
	attack_down_index=witch_rod_attack_down_index;
	attack_left_index=witch_rod_attack_left_index;
	attack_right_index=witch_rod_attack_right_index;

    animations[move_up_index]= new Animation (witch_rod_up, witch_rod_width, witch_rod_height, witch_rod_movement_states);
    animations[move_down_index]= new Animation (witch_rod_down, witch_rod_width, witch_rod_height, witch_rod_movement_states);
    animations[move_left_index]= new Animation (witch_rod_left, witch_rod_width, witch_rod_height, witch_rod_movement_states);
    animations[move_right_index]= new Animation (witch_rod_right, witch_rod_width, witch_rod_height, witch_rod_movement_states);

    animations[attack_up_index]= new Animation (witch_rod_attack_up, witch_rod_width, witch_rod_height, witch_rod_attack_states);
    animations[attack_down_index]= new Animation (witch_rod_attack_down, witch_rod_width, witch_rod_height, witch_rod_attack_states);
    animations[attack_left_index]= new Animation (witch_rod_attack_left, witch_rod_width, witch_rod_height, witch_rod_attack_states);
    animations[attack_right_index]= new Animation (witch_rod_attack_right, witch_rod_width, witch_rod_height, witch_rod_attack_states);


}