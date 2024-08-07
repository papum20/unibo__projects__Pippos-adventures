#include "enemies/witch.hpp"

Witch::Witch():Enemy(){
    speed = SPEED_WITCH;
    idle_index=witch_idle_index;
    move_up_index=witch_move_up_index;
    move_down_index=witch_move_down_index;
    move_right_index=witch_move_right_index;
    move_left_index=witch_move_left_index;

    animations[idle_index]=new Animation (witch_idle, Coordinate(witch_width, witch_height), witch_idle_states);
    animations[move_up_index]=new Animation (witch_move_up, Coordinate(witch_width, witch_height), witch_move_up_states);
    animations[move_left_index]=new Animation (witch_move_left, Coordinate(witch_width, witch_height), witch_move_left_states);
    animations[move_right_index]=new Animation (witch_move_right, Coordinate(witch_width, witch_height), witch_move_right_states);
    animations[move_down_index]=new Animation (witch_move_down, Coordinate(witch_width, witch_height), witch_move_down_states);

    points_given=witch_points;
    
    change_armor(new armor());
    change_weapon(new Witch_Rod());

    maxHealth=Math::randomStep(70, 90, 10);
    curHealth=maxHealth;
    size=Coordinate (witch_width, witch_depth);

    animation_rate=animation_rate*ranged_rate;
    animation_counter=animation_rate;
}

Witch::Witch(pCharacter p):Enemy(p){
    speed = SPEED_WITCH;
    idle_index=witch_idle_index;
    move_up_index=witch_move_up_index;
    move_down_index=witch_move_down_index;
    move_right_index=witch_move_right_index;
    move_left_index=witch_move_left_index;

    animations[idle_index]=new Animation (witch_idle, Coordinate(witch_width, witch_height), witch_idle_states);
    animations[move_up_index]=new Animation (witch_move_up, Coordinate(witch_width, witch_height), witch_move_up_states);
    animations[move_left_index]=new Animation (witch_move_left, Coordinate(witch_width, witch_height), witch_move_left_states);
    animations[move_right_index]=new Animation (witch_move_right, Coordinate(witch_width, witch_height), witch_move_right_states);
    animations[move_down_index]=new Animation (witch_move_down, Coordinate(witch_width, witch_height), witch_move_down_states);

    points_given=witch_points;
    
    change_armor(new armor());
    change_weapon(new Witch_Rod());

    maxHealth=Math::randomStep(70, 90, 10);
    curHealth=maxHealth;
    size=Coordinate (witch_width, witch_depth);

    animation_rate=animation_rate*ranged_rate;
    animation_counter=animation_rate;
}
