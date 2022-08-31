#include "fireball.hpp"

Fireball::Fireball(Weapon w):Projectile(w){
    move_up_index=fireball_up_index;
    move_down_index=fireball_down_index;
    move_left_index=fireball_left_index;
    move_right_index=fireball_right_index;

    animations[move_up_index]=new Animation (fireball_up, fireball_vertical_width, fireball_vertical_height);
    animations[move_down_index]=new Animation (fireball_down, fireball_vertical_width, fireball_vertical_height);
    animations[move_left_index]=new Animation (fireball_left, fireball_horizontal_width, fireball_horizontal_height);
    animations[move_right_index]=new Animation (fireball_right, fireball_horizontal_width, fireball_horizontal_height);



}