#include "projectile.hpp"
Projectile::Projectile(){

}

Projectile::Projectile(pWeapon w):Physical(){
    danno_fisico=w->danno_fisico;
    danno_magico=w->danno_magico;
    direction=w->direction;
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

