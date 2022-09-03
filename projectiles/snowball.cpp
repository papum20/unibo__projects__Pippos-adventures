#include "snowball.hpp"

Snowball::Snowball(pWeapon w):Projectile(w){
    move_up_index=snowball_up_index;
    move_down_index=snowball_down_index;
    move_left_index=snowball_left_index;
    move_right_index=snowball_right_index;

    animations[move_up_index]=new Animation (snowball_up, snowball_vertical_width, snowball_vertical_height);
    animations[move_down_index]=new Animation (snowball_down, snowball_vertical_width, snowball_vertical_height);
    animations[move_left_index]=new Animation (snowball_left, snowball_horizontal_width, snowball_horizontal_height);
    animations[move_right_index]=new Animation (snowball_right, snowball_horizontal_width, snowball_horizontal_height);

    horizontal_size=Coordinate (snowball_horizontal_width, snowball_horizontal_height);
    vertical_size=Coordinate (snowball_vertical_width,snowball_vertical_height);

}