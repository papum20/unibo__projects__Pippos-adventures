#include "sword.hpp"
#include <cstring> 

sword::sword (int d_f, int d_m, float v_a, char rar[], Character own):Weapon (d_f, d_m, v_a, own){
    calculate_coordinate();
}

void sword::calculalte_coordinate(){
    Coordinate newcoord;
    newcoord=owner->pos;
    if (owner->direction='r'){
        newcoord.x=newcoord.x-sword_right_width;
        newcoord.y--;
    }
    if (owner->direction='l'){
        newcoord.x=newcoord.x+owner->width;                     //da cambiare se pg hanno width diverse con animazioni diverse   
        newcoord.y--;

    }
    if (owner->direction='u'){
        newcoord.x=newcoord.x-sword_right_width;
        newcoord.y--;
    }
    
    this->pos=newcoord;
}
