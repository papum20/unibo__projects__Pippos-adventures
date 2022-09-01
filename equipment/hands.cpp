#include "hands.hpp"

Hands::Hands():Weapon(){

}

Hands::Hands(int d_f, float d_m, const char rar[]):Weapon(d_f, d_m, rar){
    apply_rarity();
}