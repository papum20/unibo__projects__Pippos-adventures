#include "hands.hpp"

Hands::Hands(int d_f, float d_m, char rar[]):Weapon(d_f, d_m, rar){
    Weapon::apply_rarity();
}