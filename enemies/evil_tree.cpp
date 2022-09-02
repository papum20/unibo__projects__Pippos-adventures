#include "evil_tree.hpp"

Evil_tree::Evil_tree():Enemy(){
    tree_branch= new Tree_branch();
    armatura= new armor();
	collana= new necklace();
	stivali= new boots();
	elmo= new helm();

    idle_index=tree_idle_index;
    move_up_index=tree_move_up_index;
    move_down_index=tree_move_down_index;
    move_right_index=tree_move_right_index;
    move_left_index=tree_move_left_index;

    animations[idle_index]=new Animation (tree_idle, tree_width, tree_height, tree_idle_states);
    animations[move_up_index]=new Animation (tree_move_up, tree_width, tree_height, tree_move_up_states);
    animations[move_left_index]=new Animation (tree_move_left, tree_width, tree_height, tree_move_left_states);
    animations[move_right_index]=new Animation (tree_move_right, tree_width, tree_height, tree_move_right_states);
    animations[move_down_index]=new Animation (tree_move_down, tree_width, tree_height, tree_move_down_states);

    points_given=tree_points;

    equipaggiamento.arma=tree_branch;
    equipaggiamento.collana=collana;
    equipaggiamento.armatura=armatura;
    equipaggiamento.stivali=stivali;
    equipaggiamento.elmo=elmo;
    equipaggiamento.scudo=NULL;

    maxHealth=Math::randomStep(70, 100, 10);

}