#include "weapon.hpp"

Weapon::Weapon (int danno_f, int danno_m, float velcoita_a, Character own){
    danno_fisico=danno_f;
    danno_magico=danno_m;
    velocita_attacco=velocita_a;
    owner=own;
}