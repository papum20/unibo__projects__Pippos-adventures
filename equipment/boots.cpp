#include <cstring> 
#include "boots.hpp"

Stivali::Stivali (int dif, int d_mag, char rar[]):item_difensivi (dif, d_mag, rar){
    item_difensivi::apply_rarity();
}