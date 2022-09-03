#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "animate.hpp"
#include "weapon.hpp"
#include "animation.hpp"


class Projectile: public Animate{
    protected:
        Coordinate horizontal_size;
		Coordinate vertical_size;
    public:
        int danno_fisico;
        int danno_magico;
        int shooter_id;
        Projectile();
        Projectile (pWeapon w);

        void update (pMap map);
        int calculate_damage(pCharacter c);
};

typedef Projectile *pProjectile;

#endif