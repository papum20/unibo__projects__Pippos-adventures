#include "zombie.hpp"

Zombie::Zombie():Enemy(){
    size=Coordinate (zombie_width, zombie_depth);
    speed = SPEED_ZOMBIE;

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

    change_weapon(new Zombie_hands());
    change_armor(new armor());

    maxHealth=Math::randomStep(50, 80, 10);
    curHealth=maxHealth;
}
Zombie::Zombie(pCharacter p):Enemy(p){
    speed = SPEED_ZOMBIE;
    size=Coordinate (zombie_width, zombie_depth);

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

    change_weapon(new Zombie_hands());
    change_armor(new armor());

    maxHealth=Math::randomStep(50, 80, 10);
    curHealth=maxHealth;
}