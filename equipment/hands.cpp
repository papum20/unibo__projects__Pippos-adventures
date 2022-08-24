#include "hands.hpp"

Hands::Hands(int d_f, float d_m, const char rar[], const char n[], const char desc[]):Weapon(d_f, d_m, rar, n, desc){
    Weapon::apply_rarity();
}