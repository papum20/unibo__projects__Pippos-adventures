#include "tree_branch.hpp"

Tree_branch::Tree_branch():Hands(){
    danno_fisico_iniziale=Math::randomStep(30, 50, 5);
    danno_magico_iniziale=Math::randomStep(30, 50, 5);

    move_up_index=tree_branch_up_index;
	move_up_index=tree_branch_down_index;
	move_left_index=tree_branch_left_index;
	move_right_index=tree_branch_right_index;

	attack_up_index=tree_branch_attack_up_index;
	attack_down_index=tree_branch_attack_down_index;
	attack_left_index=tree_branch_attack_left_index;
	attack_right_index=tree_branch_attack_right_index;

    animations[move_up_index]= new Animation (tree_branch_up, Coordinate(tree_branch_width, tree_branch_height), tree_branch_movement_states);
    animations[move_down_index]= new Animation (tree_branch_down, Coordinate(tree_branch_width, tree_branch_height), tree_branch_movement_states);
    animations[move_left_index]= new Animation (tree_branch_left, Coordinate(tree_branch_width, tree_branch_height), tree_branch_movement_states);
    animations[move_right_index]= new Animation (tree_branch_right, Coordinate(tree_branch_width, tree_branch_height), tree_branch_movement_states);

    animations[attack_up_index]= new Animation (tree_branch_attack_up, Coordinate(tree_branch_width, tree_branch_height), tree_branch_attack_states);
    animations[attack_down_index]= new Animation (tree_branch_attack_down, Coordinate(tree_branch_width, tree_branch_height), tree_branch_attack_states);
    animations[attack_left_index]= new Animation (tree_branch_attack_left, Coordinate(tree_branch_width, tree_branch_height), tree_branch_attack_states);
    animations[attack_right_index]= new Animation (tree_branch_attack_right, Coordinate(tree_branch_width, tree_branch_height), tree_branch_attack_states);

    is_melee=true;
    owner_id=ID_ENEMY_S;
    
    horizontal_size=Coordinate(tree_horizontal_attack_width, tree_horizontal_attack_height);
    vertical_size=Coordinate(tree_vertical_attack_width, tree_vertical_attack_height);
}