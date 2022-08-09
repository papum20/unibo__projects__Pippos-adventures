#include "projectile.hpp"

Projectile::Projectile(int d, int w, int h, p_Animation animazioni[], bool e, bool p){
    danno=d;
    width=w;
    height=h;
    enemy=e;
    player=p;
}