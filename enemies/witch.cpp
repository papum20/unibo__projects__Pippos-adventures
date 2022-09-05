#include "witch.hpp"

Witch::Witch(pCharacter p):Enemy(p){
    witch_rod= new Witch_Rod();
    armatura= new armor();
    collana= new necklace();
    
    idle_index=witch_idle_index;
    move_up_index=witch_move_up_index;
    move_down_index=witch_move_down_index;
    move_right_index=witch_move_right_index;
    move_left_index=witch_move_left_index;

    animations[idle_index]=new Animation (witch_idle, Coordinate(witch_width, witch_height), witch_idle_states);
    animations[move_up_index]=new Animation (witch_move_up, Coordinate(witch_width, witch_height), witch_move_up_states);
    animations[move_left_index]=new Animation (witch_move_left, Coordinate(witch_width, witch_height), witch_move_left_states);
    animations[move_right_index]=new Animation (witch_move_right, Coordinate(witch_width, witch_height), witch_move_right_states);
    animations[move_down_index]=new Animation (witch_move_down, Coordinate(witch_width, witch_height), witch_move_down_states);

    points_given=witch_points;
    
    equipaggiamento.arma=witch_rod;
    equipaggiamento.armatura=armatura;
    equipaggiamento.collana=collana;
    equipaggiamento.elmo=NULL;
    equipaggiamento.scudo=NULL;
    equipaggiamento.stivali=NULL;

    maxHealth=Math::randomStep(40, 70, 10);

}