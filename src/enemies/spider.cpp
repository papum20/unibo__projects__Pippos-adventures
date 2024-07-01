#include "enemies/spider.hpp"

Spider::Spider():Enemy(){
    idle_index=spider_idle_index;
    move_up_index=spider_move_up_index;
    move_down_index=spider_move_down_index;
    move_right_index=spider_move_right_index;
    move_left_index=spider_move_left_index;

    animations[idle_index]=new Animation (spider_idle, Coordinate(spider_width, spider_height), spider_idle_states);
    animations[move_up_index]=new Animation (spider_move_up, Coordinate(spider_width, spider_height), spider_move_up_states);
    animations[move_left_index]=new Animation (spider_move_left, Coordinate(spider_width, spider_height), spider_move_left_states);
    animations[move_right_index]=new Animation (spider_move_right, Coordinate(spider_width, spider_height), spider_move_right_states);
    animations[move_down_index]=new Animation (spider_move_down, Coordinate(spider_width, spider_height), spider_move_down_states);

    points_given=spider_points;

    change_armor(new armor());
    change_weapon(new Spider_legs());

    maxHealth=Math::randomStep(45, 55, 10);
    curHealth=maxHealth;
    size=Coordinate (spider_width, spider_depth);
    speed = SPEED_SPIDER;
}

Spider::Spider(pCharacter p):Enemy(p){
    idle_index=spider_idle_index;
    move_up_index=spider_move_up_index;
    move_down_index=spider_move_down_index;
    move_right_index=spider_move_right_index;
    move_left_index=spider_move_left_index;

    animations[idle_index]=new Animation (spider_idle, Coordinate(spider_width, spider_height), spider_idle_states);
    animations[move_up_index]=new Animation (spider_move_up, Coordinate(spider_width, spider_height), spider_move_up_states);
    animations[move_left_index]=new Animation (spider_move_left, Coordinate(spider_width, spider_height), spider_move_left_states);
    animations[move_right_index]=new Animation (spider_move_right, Coordinate(spider_width, spider_height), spider_move_right_states);
    animations[move_down_index]=new Animation (spider_move_down, Coordinate(spider_width, spider_height), spider_move_down_states);

    points_given=spider_points;

    change_armor(new armor());
    change_weapon(new Spider_legs());


    maxHealth=Math::randomStep(45, 55, 10);
    curHealth=maxHealth;
    size=Coordinate (spider_width, spider_depth);
    speed = SPEED_SPIDER;
}
