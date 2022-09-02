#include "fire_spirit.hpp"

Fire_spirit::Fire_spirit():Enemy(){
    fire_spirit_hands= new Fire_spirit_hands();
    collana= new necklace();

    idle_index=fire_spirit_idle_index;
    move_up_index=fire_spirit_move_up_index;
    move_down_index=fire_spirit_move_down_index;
    move_right_index=fire_spirit_move_right_index;
    move_left_index=fire_spirit_move_left_index;

    animations[idle_index]=new Animation (fire_spirit_idle, fire_spirit_width, fire_spirit_height, fire_spirit_idle_states);
    animations[move_up_index]=new Animation (fire_spirit_move_up, fire_spirit_width, fire_spirit_height, fire_spirit_move_up_states);
    animations[move_left_index]=new Animation (fire_spirit_move_left, fire_spirit_width, fire_spirit_height, fire_spirit_move_left_states);
    animations[move_right_index]=new Animation (fire_spirit_move_right, fire_spirit_width, fire_spirit_height, fire_spirit_move_right_states);
    animations[move_down_index]=new Animation (fire_spirit_move_down, fire_spirit_width, fire_spirit_height, fire_spirit_move_down_states);

    points_given=fire_spirit_points;

    equipaggiamento.arma=fire_spirit_hands;
    equipaggiamento.collana=collana;
    equipaggiamento.scudo=NULL;
    equipaggiamento.stivali=NULL;
    equipaggiamento.armatura=NULL;
    equipaggiamento.elmo=NULL;

    maxHealth=Math::randomStep(20, 30, 10);
}