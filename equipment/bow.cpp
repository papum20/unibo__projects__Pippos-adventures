#include "bow.hpp"
#include <cstring> 

Arco::Arco (int d_f, int d_m, const char rar[]):Weapon (d_f, d_m, rar){
    Weapon::apply_rarity();
}
