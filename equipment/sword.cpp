#include "../sword.hpp"

sword::sword():Weapon(){
    danno_fisico_iniziale=Math::randomStep(20, 40, 5);
    danno_magico_iniziale=0;

    move_up_index=sword_up_index;
	move_up_index=sword_down_index;
	move_left_index=sword_left_index;
	move_right_index=sword_right_index;

	attack_up_index=sword_attack_up_index;
	attack_down_index=sword_attack_down_index;
	attack_left_index=sword_attack_left_index;
	attack_right_index=sword_attack_right_index;

    animations[move_up_index]= new Animation (sword_up, Coordinate(sword_width, sword_height), sword_movement_states);
    animations[move_down_index]= new Animation (sword_down, Coordinate(sword_width, sword_height), sword_movement_states);
    animations[move_left_index]= new Animation (sword_left, Coordinate(sword_width, sword_height), sword_movement_states);
    animations[move_right_index]= new Animation (sword_right, Coordinate(sword_width, sword_height), sword_movement_states);

    animations[attack_up_index]= new Animation (sword_attack_up, Coordinate(sword_width, sword_height), sword_vertical_attack_states);
    animations[attack_down_index]= new Animation (sword_attack_down, Coordinate(sword_width, sword_height), sword_vertical_attack_states);
    animations[attack_left_index]= new Animation (sword_attack_left, Coordinate(sword_width, sword_height), sword_horizontal_attack_states);
    animations[attack_right_index]= new Animation (sword_attack_right, Coordinate(sword_width, sword_height), sword_horizontal_attack_states);
    
    is_melee=true;
    owner_id=ID_PLAYER;
    strcpy (description, sword_description);

    horizontal_size=Coordinate(sword_horizontal_attack_width, sword_horizontal_attack_height);
    vertical_size=Coordinate(sword_vertical_attack_width, sword_vertical_attack_height);
}

