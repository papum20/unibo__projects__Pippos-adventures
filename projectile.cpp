#include "projectile.hpp"

Projectile::Projectile(Weapon w, p_Animation animazioni[]):Physical(){
    danno_fisico=w.danno_fisico;
    danno_magico=w.danno_magico;
}

void Projectile::cast_direction (Character c){
    switch (c.direction){
        case 'u':
            direction='u';
            break;
        case 'd':
            direction='d';
            break;
        case 'l':
            direction='l';
            break;
        case 'r':
            direction='r';
            break;
    }
}

