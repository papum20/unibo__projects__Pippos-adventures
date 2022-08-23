#include "rod.hpp"
#include <cstring>

Bastone_magico::Bastone_Magico (int d_f, int d_m, const char rar[], const char n[], const char desc[]):Weapon (d_f, d_m, rar, n, desc){
    Weapon::apply_rarity();
}