#include "tree_branch.hpp"

Tree_branch::Tree_branch():Hands(){
    move_up_index=tree_branch_up_index;
	move_up_index=tree_branch_down_index;
	move_left_index=tree_branchleft_index;
	move_right_index=tree_branch_right_index;

	attack_up_index=tree_branch_attack_up_index;
	attack_down_index=tree_branch_attack_down_index;
	attack_left_index=tree_branch_attack_left_index;
	attack_right_index=tree_branch_attack_right_index;

    animations[move_up_index]= new Animation (tree_branch_up, tree_branch_width, tree_branch_height, tree_branch_movement_states);
    animations[move_down_index]= new Animation (tree_branch_down, tree_branch_width, tree_branch_height, tree_branch_movement_states);
    animations[move_left_index]= new Animation (tree_branch_left, tree_branch_width, tree_branch_height, tree_branch_movement_states);
    animations[move_right_index]= new Animation (tree_branch_right, tree_branch_width, tree_branch_height, tree_branch_movement_states);

    animations[attack_up_index]= new Animation (tree_branch_attack_up, tree_branch_width, tree_branch_height, tree_branch_attack_states);
    animations[attack_down_index]= new Animation (tree_branch_attack_down, tree_branch_width, tree_branch_height, tree_branch_attack_states);
    animations[attack_left_index]= new Animation (tree_branch_attack_left, tree_branch_width, tree_branch_height, tree_branch_attack_states);
    animations[attack_right_index]= new Animation (tree_branch_attack_right, tree_branch_width, tree_branch_height, tree_branch_attack_states);
}