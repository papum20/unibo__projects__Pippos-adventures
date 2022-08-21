#include "rod.hpp"
#include <cstring>

Bastone_magico::Bastone_Magico (int d_f, int d_m, char rar[]):Weapon (d_f, d_m, rar){
    Weapon::apply_rarity();
}