#include "equipment/player_rod.hpp"

Player_Rod::Player_Rod():Rod(){
    danno_fisico_iniziale=0;
    danno_magico_iniziale=Math::randomStep(20, 50, 5);
    apply_rarity();

    move_up_index=player_rod_up_index;
	move_down_index=player_rod_down_index;
	move_left_index=player_rod_left_index;
	move_right_index=player_rod_right_index;

	attack_up_index=player_rod_attack_up_index;
	attack_down_index=player_rod_attack_down_index;
	attack_left_index=player_rod_attack_left_index;
	attack_right_index=player_rod_attack_right_index;

    animations[move_up_index]= new Animation (player_rod_up, Coordinate(player_rod_width, player_rod_height), player_rod_movement_states);
    animations[move_down_index]= new Animation (player_rod_down, Coordinate(player_rod_width, player_rod_height), player_rod_movement_states);
    animations[move_left_index]= new Animation (player_rod_left, Coordinate(player_rod_width, player_rod_height), player_rod_movement_states);
    animations[move_right_index]= new Animation (player_rod_right, Coordinate(player_rod_width, player_rod_height), player_rod_movement_states);

    animations[attack_up_index]= new Animation (player_rod_attack_up, Coordinate(player_rod_width, player_rod_height), player_rod_attack_states);
    animations[attack_down_index]= new Animation (player_rod_attack_down, Coordinate(player_rod_width, player_rod_height), player_rod_attack_states);
    animations[attack_left_index]= new Animation (player_rod_attack_left, Coordinate(player_rod_width, player_rod_height), player_rod_attack_states);
    animations[attack_right_index]= new Animation (player_rod_attack_right, Coordinate(player_rod_width, player_rod_height), player_rod_attack_states);

    is_melee=false;
    owner_id=ID_PLAYER;

    strcpy (description, player_rod_description);
    strcpy (name, player_rod_name);

    horizontal_attack_states=player_rod_attack_states;
    vertical_attack_states=player_rod_attack_states;
    current_animation = move_right_index;

    projectile= Spell(danno_fisico, danno_magico, direction, owner_id);
    animation_rate=animation_rate;
    animation_counter=animation_rate;
}
