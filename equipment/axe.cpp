#include "axe.hpp"
#include <cstring>

Ascia::Ascia (int d_f, int d_m, char rar[]):Weapon (d_f, d_m, rar){
    Weapon::apply_rarity();
}