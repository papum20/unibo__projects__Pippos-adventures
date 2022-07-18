#include "bat.hpp"


Bat::Bat():Enemy(Max_Health_Bat, bat_weapon){

    animation[idle_index_bat] = tail_insert(animation[idle_index_bat], idle_bat[0], bat_height, bat_width);
    for(int i=0; i<movement_animation_bat_n; i++){
      animation[movement_index_bat] = tail_insert(animation[movement_index_bat], movement_bat[i], bat_height, bat_width);
    }
}

