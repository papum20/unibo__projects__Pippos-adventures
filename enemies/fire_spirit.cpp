#include "fire_spirit.hpp"

Fire_spirit::Fire_spirit():Enemy(){

    idle_index=fire_spirit_idle_index;
    move_up_index=fire_spirit_move_up_index;
    move_down_index=fire_spirit_move_down_index;
    move_right_index=fire_spirit_move_right_index;
    move_left_index=fire_spirit_move_left_index;

    animations[idle_index]=new Animation (fire_spirit_idle, Coordinate(fire_spirit_width, fire_spirit_height), fire_spirit_idle_states);
    animations[move_up_index]=new Animation (fire_spirit_move_up, Coordinate(fire_spirit_width, fire_spirit_height), fire_spirit_move_up_states);
    animations[move_left_index]=new Animation (fire_spirit_move_left, Coordinate(fire_spirit_width, fire_spirit_height), fire_spirit_move_left_states);
    animations[move_right_index]=new Animation (fire_spirit_move_right, Coordinate(fire_spirit_width, fire_spirit_height), fire_spirit_move_right_states);
    animations[move_down_index]=new Animation (fire_spirit_move_down, Coordinate(fire_spirit_width, fire_spirit_height), fire_spirit_move_down_states);

    points_given=fire_spirit_points;

    change_weapon(new Fire_spirit_hands());
    change_necklace(new necklace());

    maxHealth=Math::randomStep(150, 200, 10);
    curHealth=maxHealth;
    size=Coordinate (fire_spirit_width, fire_spirit_depth);
}

Fire_spirit::Fire_spirit(pCharacter p):Enemy(p){

    idle_index=fire_spirit_idle_index;
    move_up_index=fire_spirit_move_up_index;
    move_down_index=fire_spirit_move_down_index;
    move_right_index=fire_spirit_move_right_index;
    move_left_index=fire_spirit_move_left_index;

    animations[idle_index]=new Animation (fire_spirit_idle, Coordinate(fire_spirit_width, fire_spirit_height), fire_spirit_idle_states);
    animations[move_up_index]=new Animation (fire_spirit_move_up, Coordinate(fire_spirit_width, fire_spirit_height), fire_spirit_move_up_states);
    animations[move_left_index]=new Animation (fire_spirit_move_left, Coordinate(fire_spirit_width, fire_spirit_height), fire_spirit_move_left_states);
    animations[move_right_index]=new Animation (fire_spirit_move_right, Coordinate(fire_spirit_width, fire_spirit_height), fire_spirit_move_right_states);
    animations[move_down_index]=new Animation (fire_spirit_move_down, Coordinate(fire_spirit_width, fire_spirit_height), fire_spirit_move_down_states);

    points_given=fire_spirit_points;

    change_weapon(new Fire_spirit_hands());
    change_necklace(new necklace());

    maxHealth=Math::randomStep(150, 200, 10);
    curHealth=maxHealth;
    size=Coordinate (fire_spirit_width, fire_spirit_depth);
}
