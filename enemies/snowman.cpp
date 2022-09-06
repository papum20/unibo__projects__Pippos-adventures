#include "snowman.hpp"

Snowman::Snowman():Enemy(){
    snowman_hands= new Snowman_hands();
    armatura= new armor();
    stivali= new boots();
    collana= new necklace();

    idle_index=snowman_idle_index;
    move_up_index=snowman_move_up_index;
    move_down_index=snowman_move_down_index;
    move_right_index=snowman_move_right_index;
    move_left_index=snowman_move_left_index;

    animations[idle_index]=new Animation (snowman_idle, Coordinate(snowman_width, snowman_height), snowman_idle_states);
    animations[move_up_index]=new Animation (snowman_move_up, Coordinate(snowman_width, snowman_height), snowman_move_up_states);
    animations[move_left_index]=new Animation (snowman_move_left, Coordinate(snowman_width, snowman_height), snowman_move_left_states);
    animations[move_right_index]=new Animation (snowman_move_right, Coordinate(snowman_width, snowman_height), snowman_move_right_states);
    animations[move_down_index]=new Animation (snowman_move_down, Coordinate(snowman_width, snowman_height), snowman_move_down_states);

    points_given=snowman_points;

    change_armor(armatura);
    change_necklace(collana);
    change_boots(stivali);
    change_weapon(snowman_hands);
    
    maxHealth=Math::randomStep(40, 70, 10);
    curHealth=maxHealth;
    size=Coordinate (snowman_width, snowman_depth);
};

Snowman::Snowman(pCharacter p):Enemy(p){
    snowman_hands= new Snowman_hands();
    armatura= new armor();
    stivali= new boots();
    collana= new necklace();

    idle_index=snowman_idle_index;
    move_up_index=snowman_move_up_index;
    move_down_index=snowman_move_down_index;
    move_right_index=snowman_move_right_index;
    move_left_index=snowman_move_left_index;

    animations[idle_index]=new Animation (snowman_idle, Coordinate(snowman_width, snowman_height), snowman_idle_states);
    animations[move_up_index]=new Animation (snowman_move_up, Coordinate(snowman_width, snowman_height), snowman_move_up_states);
    animations[move_left_index]=new Animation (snowman_move_left, Coordinate(snowman_width, snowman_height), snowman_move_left_states);
    animations[move_right_index]=new Animation (snowman_move_right, Coordinate(snowman_width, snowman_height), snowman_move_right_states);
    animations[move_down_index]=new Animation (snowman_move_down, Coordinate(snowman_width, snowman_height), snowman_move_down_states);

    points_given=snowman_points;

    change_armor(armatura);
    change_necklace(collana);
    change_boots(stivali);
    change_weapon(snowman_hands);
    
    maxHealth=Math::randomStep(40, 70, 10);
    curHealth=maxHealth;
    size=Coordinate (snowman_width, snowman_depth);
};