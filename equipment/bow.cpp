#include "bow.hpp"
#include <cstring> 

Arco::Arco():Weapon(){
    
}

Arco::Arco (int d_f, int d_m, const char rar[], const char n[], const char desc[]):Weapon (d_f, d_m, rar, n, desc){
    move_up_index=bow_up_index;
	move_up_index=bow_down_index;
	move_left_index=bow_left_index;
	move_right_index=bow_right_index;

	attack_up_index=bow_attack_up_index;
	attack_down_index=bow_attack_down_index;
	attack_left_index=bow_attack_left_index;
	attack_right_index=bow_attack_right_index;

    animations[move_up_index]= new Animation (bow_up, bow_width, bow_height, bow_movement_states);
    animations[move_down_index]= new Animation (bow_down, bow_width, bow_height, bow_movement_states);
    animations[move_left_index]= new Animation (bow_left, bow_width, bow_height, bow_movement_states);
    animations[move_right_index]= new Animation (bow_right, bow_width, bow_height, bow_movement_states);

    animations[attack_up_index]= new Animation (bow_attack_up, bow_width, bow_height, bow_attack_states);
    animations[attack_down_index]= new Animation (bow_attack_down, bow_width, bow_height, bow_attack_states);
    animations[attack_left_index]= new Animation (bow_attack_left, bow_horizontal_attack_width, bow_horizontal_attack_height, bow_attack_states);
    animations[attack_right_index]= new Animation (bow_attack_right, bow_horizontal_attack_width, bow_horizontal_attack_height, bow_attack_states);
    
    is_melee=false;

    apply_rarity();
}
