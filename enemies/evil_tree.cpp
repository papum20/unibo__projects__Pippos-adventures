#include "evil_tree.hpp"

Evil_tree::Evil_tree():Enemy(){
    idle_index=tree_idle_index;
    move_up_index=tree_move_up_index;
    move_down_index=tree_move_down_index;
    move_right_index=tree_move_right_index;
    move_left_index=tree_move_left_index;

    animations[idle_index]=new Animation (tree_idle, Coordinate(tree_width, tree_height), tree_idle_states);
    animations[move_up_index]=new Animation (tree_move_up, Coordinate(tree_width, tree_height), tree_move_up_states);
    animations[move_left_index]=new Animation (tree_move_left, Coordinate(tree_width, tree_height), tree_move_left_states);
    animations[move_right_index]=new Animation (tree_move_right, Coordinate(tree_width, tree_height), tree_move_right_states);
    animations[move_down_index]=new Animation (tree_move_down, Coordinate(tree_width, tree_height), tree_move_down_states);

    points_given=tree_points;

    tree_branch=new Tree_branch();
    armor= new armor();
    necklace=new necklace();
    boots=new boots();
    helm=new helm();

    change_weapon(tree_branch);
    change_armor(armor);
    change_necklace(necklace);
    change_boots(boots);
    change_helm(helm);

    maxHealth=Math::randomStep(70, 100, 10);
    curHealth=maxHealth;
    size=Coordinate (tree_width, tree_depth);
}

Evil_tree::Evil_tree(pCharacter p):Enemy(p){
    idle_index=tree_idle_index;
    move_up_index=tree_move_up_index;
    move_down_index=tree_move_down_index;
    move_right_index=tree_move_right_index;
    move_left_index=tree_move_left_index;

    animations[idle_index]=new Animation (tree_idle, Coordinate(tree_width, tree_height), tree_idle_states);
    animations[move_up_index]=new Animation (tree_move_up, Coordinate(tree_width, tree_height), tree_move_up_states);
    animations[move_left_index]=new Animation (tree_move_left, Coordinate(tree_width, tree_height), tree_move_left_states);
    animations[move_right_index]=new Animation (tree_move_right, Coordinate(tree_width, tree_height), tree_move_right_states);
    animations[move_down_index]=new Animation (tree_move_down, Coordinate(tree_width, tree_height), tree_move_down_states);

    points_given=tree_points;

    change_weapon(new Tree_branch());
    change_armor(new armor());
    change_necklace(new necklace());
    change_boots(new boots());
    change_helm(new helm());

    maxHealth=Math::randomStep(70, 100, 10);
    curHealth=maxHealth;
    size=Coordinate (tree_width, tree_depth);
}
