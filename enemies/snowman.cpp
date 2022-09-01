#include "snowman.hpp"

Snowman::Snowman():Enemy(){
    idle_index=snowman_idle_index;
    move_up_index=snowman_move_up_index;
    move_down_index=snowman_move_down_index;
    move_right_index=snowman_move_right_index;
    move_left_index=snowman_move_left_index;

    animations[idle_index]=new Animation (snowman_idle, ENEMY_ANIMATION_WIDTH, ENEMY_ANIMATION_HEIGHT, snowman_idle_states);
    animations[move_up_index]=new Animation (snowman_move_up, ENEMY_ANIMATION_WIDTH, ENEMY_ANIMATION_HEIGHT, snowman_move_up_states);
    animations[move_left_index]=new Animation (snowman_move_left, ENEMY_ANIMATION_WIDTH, ENEMY_ANIMATION_HEIGHT, snowman_move_left_states);
    animations[move_right_index]=new Animation (snowman_move_right, ENEMY_ANIMATION_WIDTH, ENEMY_ANIMATION_HEIGHT, snowman_move_right_states);
    animations[move_down_index]=new Animation (snowman_move_down, ENEMY_ANIMATION_WIDTH, ENEMY_ANIMATION_HEIGHT, snowman_move_down_states);

    points_given=snowman_points;
};