#include "zombie.hpp"

Zombie::Zombie():Enemy(){
    size=Coordinate (zombie_width, zombie_depth);
    
    zombie_hands=new Zombie_hands();
    armatura= new armor();

    idle_index=zombie_idle_index;
    move_up_index=zombie_move_up_index;
    move_down_index=zombie_move_down_index;
    move_right_index=zombie_move_right_index;
    move_left_index=zombie_move_left_index;

    animations[idle_index]=new Animation (zombie_idle, Coordinate(zombie_width, zombie_height), zombie_idle_states);
    animations[move_up_index]=new Animation (zombie_move_up, Coordinate(zombie_width, zombie_height), zombie_move_up_states);
    animations[move_left_index]=new Animation (zombie_move_left, Coordinate(zombie_width, zombie_height), zombie_move_left_states);
    animations[move_right_index]=new Animation (zombie_move_right, Coordinate(zombie_width, zombie_height), zombie_move_right_states);
    animations[move_down_index]=new Animation (zombie_move_down, Coordinate(zombie_width, zombie_height), zombie_move_down_states);

    points_given=zombie_points;

    change_weapon(zombie_hands);
    change_armor(armatura);

    maxHealth=Math::randomStep(20, 40, 10);
    curHealth=maxHealth;
}
Zombie::Zombie(pCharacter p):Enemy(p){
    size=Coordinate (zombie_width, zombie_depth);
    
    zombie_hands=new Zombie_hands();
    armatura= new armor();

    idle_index=zombie_idle_index;
    move_up_index=zombie_move_up_index;
    move_down_index=zombie_move_down_index;
    move_right_index=zombie_move_right_index;
    move_left_index=zombie_move_left_index;

    animations[idle_index]=new Animation (zombie_idle, Coordinate(zombie_width, zombie_height), zombie_idle_states);
    animations[move_up_index]=new Animation (zombie_move_up, Coordinate(zombie_width, zombie_height), zombie_move_up_states);
    animations[move_left_index]=new Animation (zombie_move_left, Coordinate(zombie_width, zombie_height), zombie_move_left_states);
    animations[move_right_index]=new Animation (zombie_move_right, Coordinate(zombie_width, zombie_height), zombie_move_right_states);
    animations[move_down_index]=new Animation (zombie_move_down, Coordinate(zombie_width, zombie_height), zombie_move_down_states);

    points_given=zombie_points;

    change_weapon(zombie_hands);
    change_armor(armatura);

    maxHealth=Math::randomStep(20, 40, 10);
    curHealth=maxHealth;
}