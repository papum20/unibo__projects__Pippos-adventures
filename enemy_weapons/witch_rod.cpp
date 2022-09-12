#include "witch_rod.hpp"

Witch_Rod::Witch_Rod():Rod(){
    danno_fisico_iniziale=0;
    danno_magico_iniziale=Math::randomStep(80, 100, 5);
    apply_rarity();

    move_up_index=witch_rod_up_index;
	move_down_index=witch_rod_down_index;
	move_left_index=witch_rod_left_index;
	move_right_index=witch_rod_right_index;

	attack_up_index=witch_rod_attack_up_index;
	attack_down_index=witch_rod_attack_down_index;
	attack_left_index=witch_rod_attack_left_index;
	attack_right_index=witch_rod_attack_right_index;

    animations[move_up_index]= new Animation (witch_rod_up, Coordinate(witch_rod_width, witch_rod_height), witch_rod_movement_states);
    animations[move_down_index]= new Animation (witch_rod_down, Coordinate(witch_rod_width, witch_rod_height), witch_rod_movement_states);
    animations[move_left_index]= new Animation (witch_rod_left, Coordinate(witch_rod_width, witch_rod_height), witch_rod_movement_states);
    animations[move_right_index]= new Animation (witch_rod_right, Coordinate(witch_rod_width, witch_rod_height), witch_rod_movement_states);

    animations[attack_up_index]= new Animation (witch_rod_attack_up, Coordinate(witch_rod_width, witch_rod_height), witch_rod_attack_states);
    animations[attack_down_index]= new Animation (witch_rod_attack_down, Coordinate(witch_rod_width, witch_rod_height), witch_rod_attack_states);
    animations[attack_left_index]= new Animation (witch_rod_attack_left, Coordinate(witch_rod_width, witch_rod_height), witch_rod_attack_states);
    animations[attack_right_index]= new Animation (witch_rod_attack_right, Coordinate(witch_rod_width, witch_rod_height), witch_rod_attack_states);
    
    offset = Coordinate(witch_x_coordinate, witch_y_coordinate);
    
    owner_id=ID_ENEMY_S;
    is_melee=false;

    horizontal_attack_states=witch_rod_attack_states;
    vertical_attack_states=witch_rod_attack_states;

    projectile= Spell(danno_fisico, danno_magico, direction, owner_id);
    current_animation=0;

    animation_rate=animation_rate*ranged_rate;
    animation_counter=animation_rate;
}

