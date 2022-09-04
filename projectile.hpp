#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "animate.hpp"
//#include "weapon.hpp"
#include "animation.hpp"
#include "alive.hpp"


class Projectile: public Animate{
    protected:
        Coordinate horizontal_size;
		Coordinate vertical_size;
    public:
        int danno_fisico;
        int danno_magico;
        int shooter_id;
        Projectile();
        //Projectile (pWeapon w);
        Projectile (int fisico, int magico, char dir, int shooter);

        void update (pMap map);
        int calculate_damage(pAlive c);
};

typedef Projectile *pProjectile;


#endif