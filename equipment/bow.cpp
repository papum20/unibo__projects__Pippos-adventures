#include "bow.hpp"
#include <cstring> 

Arco::Arco():Weapon(){
    danno_fisico_iniziale=Math::randomStep(20, 50, 5);
    danno_magico_iniziale=0;
    strcpy (description, bow_description);

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
    owner_id=ID_PLAYER;

    horizontal_attack_states=bow_attack_states;
    vertical_attack_states=bow_attack_states;
}

void Arco::shoot(){
    freccia=Arrow(this);
}
