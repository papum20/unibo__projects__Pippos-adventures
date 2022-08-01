#include "player.hpp"

Player::Player():Character(p_max_health) {

	id=ID_PLAYER;
	animation[idle_index] = new Animation(idle, p_height, p_width, idle_states);
	
	animation[move_right_index] = new Animation(move_right, p_height, p_width, move_right_states);
	animation[move_left_index] = new Animation(move_left, p_height, p_width, move_left_states);
	animation[move_up_index] = new Animation(move_up, p_height, p_width, move_up_states);
	animation[move_down_index] = new Animation(move_down, p_height, p_width, move_down_states);

	animation[dash_up_index] = new Animation(dash_up, p_height, p_width, dash_up_states);
	animation[dash_down_index] = new Animation(dash_down, p_height, p_width, dash_down_states);
	animation[dash_left_index] = new Animation(dash_left, p_height, p_width, dash_left_states);
	animation[dash_right_index] = new Animation(dash_right, p_height, p_width, dash_right_states);
	
}