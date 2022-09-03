#include "weapon.hpp"

Weapon::Weapon ():item(){
    is_equipped=false;
    id=ID_WEAPON_S;
}


void Weapon::apply_rune(){
    if (this->check_rarity())
        apply_rarity();
}

void Weapon::apply_rarity (){
    if (strcmp(rarity, rare)==0){
        danno_fisico=danno_fisico_iniziale*2;
        danno_magico=danno_magico_iniziale*2;
        }
    if (strcmp (rarity, epic)==0){
        danno_fisico=danno_fisico_iniziale*3;
        danno_magico=danno_magico_iniziale*3;
    }
    if (strcmp (rarity, legendary)==0){
        danno_fisico=danno_fisico_iniziale*4;
        danno_magico=danno_magico_iniziale*4;
    }
}



Coordinate Weapon::getOffset() {
    return offset;
}
void Weapon::initiate_attack(char d){
    direction=d;
    switch (direction){
        case 'u':
            (equipaggiamento.arma)->current_animation=(equipaggiamento.arma)->attack_up_index;
            break;
        case 'd':
            (equipaggiamento.arma)->current_animation=(equipaggiamento.arma)->attack_down_index;
            break;
        case 'l':
            (equipaggiamento.arma)->current_animation=(equipaggiamento.arma)->attack_right_index;
            break;
        case 'r':
            (equipaggiamento.arma)->current_animation=(equipaggiamento.arma)->attack_left_index;
            break;
    }
}