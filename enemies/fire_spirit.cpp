#include "fire_spirit.hpp"

Fire_spirit::Fire_spirit():Enemy(){
    idle_index=fire_spirit_idle_index;
    move_up_index=fire_spirit_move_up_index;
    move_down_index=fire_spirit_move_down_index;
    move_right_index=fire_spirit_move_right_index;
    move_left_index=fire_spirit_move_left_index;

    animations[idle_index]=new Animation (fire_spirit_idle, ENEMY_ANIMATION_WIDTH, ENEMY_ANIMATION_HEIGHT, fire_spirit_idle_states);
    animations[move_up_index]=new Animation (fire_spirit_move_up, ENEMY_ANIMATION_WIDTH, ENEMY_ANIMATION_HEIGHT, fire_spirit_move_up_states);
    animations[move_left_index]=new Animation (fire_spirit_move_left, ENEMY_ANIMATION_WIDTH, ENEMY_ANIMATION_HEIGHT, fire_spirit_move_left_states);
    animations[move_right_index]=new Animation (fire_spirit_move_right, ENEMY_ANIMATION_WIDTH, ENEMY_ANIMATION_HEIGHT, fire_spirit_move_right_states);
    animations[move_down_index]=new Animation (fire_spirit_move_down, ENEMY_ANIMATION_WIDTH, ENEMY_ANIMATION_HEIGHT, fire_spirit_move_down_states);
}