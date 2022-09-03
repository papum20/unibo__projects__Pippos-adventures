#include "weapon.hpp"

Weapon::Weapon ():item(){
    is_equipped=false;
    id=ID_WEAPON_S;
    main_color = COLOR_WEAPON;
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
            current_animation=attack_up_index;
            break;
        case 'd':
            current_animation=attack_down_index;
            break;
        case 'l':
            current_animation=attack_right_index;
            break;
        case 'r':
            current_animation=attack_left_index;
            break;
    }
}


bool Weapon::animationMask(Coordinate pos) {
    return getCurrentAnimation().state[pos.single()] == CHAR_EMPTY || getCurrentAnimation().state[pos.single()] == CHAR_WEAPON_MASK;
}