#include "arrow.hpp"

Arrow::Arrow(pWeapon w):Projectile(w){
    move_up_index=arrow_up_index;
    move_down_index=arrow_down_index;
    move_left_index=arrow_left_index;
    move_right_index=arrow_right_index;

    animations[move_up_index]=new Animation (arrow_up, Coordinate(arrow_vertical_width, arrow_vertical_height));
    animations[move_down_index]=new Animation (arrow_down, Coordinate(arrow_vertical_width, arrow_vertical_height));
    animations[move_left_index]=new Animation (arrow_left, Coordinate(arrow_vertical_width, arrow_vertical_height));
    animations[move_right_index]=new Animation (arrow_right, Coordinate(arrow_vertical_width, arrow_vertical_height));

    horizontal_size=Coordinate (arrow_horizontal_width, arrow_horizontal_height);
    vertical_size=Coordinate (arrow_vertical_width,arrow_vertical_height);
}