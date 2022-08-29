#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "physical.hpp"
#include "weapon.hpp"
#include "animation.hpp"

class Projectile: public Physical{
    protected:
        int danno_fisico;
        int danno_magico;

        char direction;

        int up_width;
        int up_height;

        int down_width;
        int down_height;
        
        int right_width;
        int right_height;

        int left_width;
        int left_height;
    public:
        Projectile (Weapon w, p_Animation animazioni[]);

        void cast_direction (Character c);
};

typedef Projectile *pProjectile;

#endif