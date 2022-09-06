#include "zombie_hands.hpp"

Zombie_hands::Zombie_hands():Hands(){
    danno_fisico_iniziale=Math::randomStep(20, 40, 5);
    danno_magico_iniziale=0;
    apply_rarity();
    
    move_up_index=zombie_hands_up_index;
	move_up_index=zombie_hands_down_index;
	move_left_index=zombie_hands_left_index;
	move_right_index=zombie_hands_right_index;

	attack_up_index=zombie_hands_attack_up_index;
	attack_down_index=zombie_hands_attack_down_index;
	attack_left_index=zombie_hands_attack_left_index;
	attack_right_index=zombie_hands_attack_right_index;

    animations[move_up_index]= new Animation (zombie_hands_up, Coordinate(zombie_hands_width, zombie_hands_height), zombie_hands_movement_states);
    animations[move_down_index]= new Animation (zombie_hands_down, Coordinate(zombie_hands_width, zombie_hands_height), zombie_hands_movement_states);
    animations[move_left_index]= new Animation (zombie_hands_left, Coordinate(zombie_hands_width, zombie_hands_height), zombie_hands_movement_states);
    animations[move_right_index]= new Animation (zombie_hands_right, Coordinate(zombie_hands_width, zombie_hands_height), zombie_hands_movement_states);

    animations[attack_up_index]= new Animation (zombie_hands_attack_up, Coordinate(zombie_hands_width, zombie_hands_height), zombie_hands_attack_states);
    animations[attack_down_index]= new Animation (zombie_hands_attack_down, Coordinate(zombie_hands_width, zombie_hands_height), zombie_hands_attack_states);
    animations[attack_left_index]= new Animation (zombie_hands_attack_left, Coordinate(zombie_hands_width, zombie_hands_height), zombie_hands_attack_states);
    animations[attack_right_index]= new Animation (zombie_hands_attack_right, Coordinate(zombie_hands_width, zombie_hands_height), zombie_hands_attack_states);

    is_melee=true;
    owner_id=ID_ENEMY_S;
    horizontal_size=Coordinate(zombie_horizontal_attack_width, zombie_horizontal_attack_height);
    vertical_size=Coordinate(zombie_vertical_attack_width, zombie_vertical_attack_height);

    horizontal_attack_states=zombie_hands_attack_states;
    vertical_attack_states=zombie_hands_attack_states;
    current_animation=0;
    projectile=NULL;
}