#include "weapon.hpp"

Weapon::Weapon ():item(){
    is_equipped=false;
    id=ID_WEAPON_S;
    main_color = COLOR_WEAPON;
}


void Weapon::copyWeapon(Weapon B) {
    projectile=B.projectile;
    offset=B.offset;
    horizontal_size=B.horizontal_size;
    vertical_size=B.vertical_size;
    delta_x_horizontal=B.delta_x_horizontal;
    delta_y_vertical=B.delta_y_vertical;
    danno_fisico_iniziale=B.danno_fisico_iniziale;
    danno_magico_iniziale=B.danno_magico_iniziale;
    danno_fisico=B.danno_fisico;
    danno_magico=B.danno_magico;
    is_melee=B.is_melee;
    is_equipped=B.is_equipped;
    owner_id=B.owner_id;

    vertical_attack_states=B.vertical_attack_states;
    horizontal_attack_states=B.horizontal_attack_states;
    vertical_attack_animation=B.vertical_attack_animation;
    horizontal_attack_animation=B.horizontal_attack_animation;

    copyItem(B);
}

void Weapon::apply_rune(){
    if (this->check_rarity())
        apply_rarity();
}

void Weapon::apply_rarity (){
    if (strcmp(rarity, common)==0){
        danno_fisico=danno_fisico_iniziale;
        danno_magico=danno_magico_iniziale;
        }
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
    return getCurrentAnimation().state[pos.single()] != CHAR_EMPTY && getCurrentAnimation().state[pos.single()] != CHAR_WEAPON_MASK;
}

pProjectile Weapon::shoot() {
    pProjectile res = new Projectile;
    res->copyProjectile(*projectile);
    return res;
}