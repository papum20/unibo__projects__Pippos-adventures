#include "axe.hpp"
#include <cstring>

Ascia::Ascia (int d_f, int d_m, const char rar[], const char n[], const char desc[]):Weapon (d_f, d_m, rar, n, desc){
    Weapon::apply_rarity();
}