#include "player.hpp"

Player::Player():Character(p_max_health) {


animation[idle_index] = tail_insert(animation[idle_index], idle[0], p_height, p_width);
for(int i=0; i<2; i++){
animation[move_right_index] = tail_insert(animation[move_right_index], move_right[i], p_height, p_width);
}
for(int i=0; i<2; i++){
animation[move_left_index] = tail_insert(animation[move_left_index], move_left[i], p_height, p_width);
}
for(int i=0; i<2; i++){
animation[move_up_index] = tail_insert(animation[move_up_index], move_up[i], p_height, p_width);
}
for(int i=0; i<2; i++){
animation[move_down_index] = tail_insert(animation[move_down_index], move_down[i], p_height, p_width);
}
}