#include "spider_legs.hpp"

Spider_legs::Spider_legs():Hands(){
    danno_fisico_iniziale=Math::randomStep(30, 50, 5);
    danno_magico_iniziale=0;
    strcpy (rarity, common);

    move_up_index=spider_legs_up_index;
	move_up_index=spider_legs_down_index;
	move_left_index=spider_legs_left_index;
	move_right_index=spider_legs_right_index;

	attack_up_index=spider_legs_attack_up_index;
	attack_down_index=spider_legs_attack_down_index;
	attack_left_index=spider_legs_attack_left_index;
	attack_right_index=spider_legs_attack_right_index;

    animations[move_up_index]= new Animation (spider_legs_up, spider_legs_width, spider_legs_height, spider_legs_movement_states);
    animations[move_down_index]= new Animation (spider_legs_down, spider_legs_width, spider_legs_height, spider_legs_movement_states);
    animations[move_left_index]= new Animation (spider_legs_left, spider_legs_width, spider_legs_height, spider_legs_movement_states);
    animations[move_right_index]= new Animation (spider_legs_right, spider_legs_width, spider_legs_height, spider_legs_movement_states);

    animations[attack_up_index]= new Animation (spider_legs_attack_up, spider_legs_width, spider_legs_height, spider_legs_vertical_attack_states);
    animations[attack_down_index]= new Animation (spider_legs_attack_down, spider_legs_width, spider_legs_height, spider_legs_vertical_attack_states);
    animations[attack_left_index]= new Animation (spider_legs_attack_left, spider_legs_width, spider_legs_height, spider_legs_horizontal_attack_states);
    animations[attack_right_index]= new Animation (spider_legs_attack_right, spider_legs_width, spider_legs_height, spider_legs_horizontal_attack_states);

    is_melee=true;
}