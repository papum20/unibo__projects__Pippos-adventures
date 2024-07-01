#include "projectiles/fireball.hpp"

Fireball::Fireball(int fisico, int magico, char dir, int shooter):Projectile( fisico,  magico,  dir,  shooter){
    move_up_index=fireball_up_index;
    move_down_index=fireball_down_index;
    move_left_index=fireball_left_index;
    move_right_index=fireball_right_index;

    animations[move_up_index]=new Animation (fireball_up, Coordinate(fireball_vertical_width, fireball_vertical_height));
    animations[move_down_index]=new Animation (fireball_down, Coordinate(fireball_vertical_width, fireball_vertical_height));
    animations[move_left_index]=new Animation (fireball_left, Coordinate(fireball_horizontal_width, fireball_horizontal_height));
    animations[move_right_index]=new Animation (fireball_right, Coordinate(fireball_horizontal_width, fireball_horizontal_height));

    horizontal_size=Coordinate (fireball_horizontal_width, fireball_horizontal_height+1);
    vertical_size=Coordinate (fireball_vertical_width+1,fireball_vertical_height);

}