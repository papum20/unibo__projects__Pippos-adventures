#include "projectile.hpp"

Projectile::Projectile(Weapon w, p_Animation animazioni[])::Physical(){
    danno_fisico=w.danno_fisico;
    danno_magico=w.danno_magico;
    id=(w.owner).id;
}

void Projectile::cast_direction (Character c, int d){
    switch (d){
        case c.right_attack_index:
            direction='r';
            break;
        case c.left_attack_index:
            direction='l';
            break;
        case c.up_attack_index:
            direction='u';
            break;
        case c.down_attack_index:
            direction='d';
            break;
    }
}

