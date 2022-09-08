#include "axe.hpp"
#include <cstring>

Ascia::Ascia():Weapon(){
    danno_fisico_iniziale=Math::randomStep(20, 40, 5);
    danno_magico_iniziale=0;
    apply_rarity();

    move_up_index=axe_up_index;
	move_up_index=axe_down_index;
	move_left_index=axe_left_index;
	move_right_index=axe_right_index;

	attack_up_index=axe_attack_up_index;
	attack_down_index=axe_attack_down_index;
	attack_left_index=axe_attack_left_index;
	attack_right_index=axe_attack_right_index;

    animations[move_up_index]= new Animation (axe_up, Coordinate(axe_width, axe_height), axe_movement_states);
    animations[move_down_index]= new Animation (axe_down, Coordinate(axe_width, axe_height), axe_movement_states);
    animations[move_left_index]= new Animation (axe_left, Coordinate(axe_width, axe_height), axe_movement_states);
    animations[move_right_index]= new Animation (axe_right, Coordinate(axe_width, axe_height), axe_movement_states);

    animations[attack_up_index]= new Animation (axe_attack_up, Coordinate(axe_width, axe_height), axe_vertical_attack_states);
    animations[attack_down_index]= new Animation (axe_attack_down, Coordinate(axe_width, axe_height), axe_vertical_attack_states);
    animations[attack_left_index]= new Animation (axe_attack_left, Coordinate(axe_width, axe_height), axe_horizontal_attack_states);
    animations[attack_right_index]= new Animation (axe_attack_right, Coordinate(axe_width, axe_height), axe_horizontal_attack_states);

    is_melee=true;
    owner_id=ID_PLAYER;
    strcpy (description, axe_description);
    strcpy (name, axe_name);

    horizontal_size=Coordinate(axe_horizontal_attack_width, axe_horizontal_attack_height);
    vertical_size=Coordinate(axe_vertical_attack_width, axe_vertical_attack_height);

    horizontal_attack_states=axe_horizontal_attack_states;
    vertical_attack_states=axe_vertical_attack_states;

    vertical_attack_animation=axe_vertical_attack_animation;
    horizontal_attack_animation=axe_horizontal_attack_animation;
    current_animation=0;
}

