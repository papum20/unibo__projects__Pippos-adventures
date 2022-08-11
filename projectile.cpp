#include "projectile.hpp"

Projectile::Projectile(int d, int w, int h, pAnimation animazioni[])::Physical(){
    danno=d;
    width=w;
    height=h;
}

Projectile::void cast_direction_id (Character c, int d){
    switch (d){
        case c.dx_attacking_index:
            direction='r';
        case c.sx_attacking_index:
            direction='l';
        case c.up_attacking_index:
            direction='u';
        case c.down_attacking_index:
            direction='d';
    }

    id=c.id;
}

