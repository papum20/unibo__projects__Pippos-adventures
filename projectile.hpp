#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "physical.hpp"
#include "weapon.hpp"
#include "animation.hpp"

class Projectile: public Physical{
    protected:
        Coordinate horizontal_size;
		Coordinate vertical_size;
    public:
        int danno_fisico;
        int danno_magico;
        Projectile();
        Projectile (pWeapon w);

        void cast_direction (Character c);
};

typedef Projectile *pProjectile;

#endif