#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "physical.hpp"

Class Projectile: public Physical{
    protected:
        int danno;
        int width;
        int height;
        int id;
        char direction;
    public:
        Projectile (int d, int w, int h, p_Animation animazioni[], bool e, bool p);

        void cast_direction_id (Character c, int d);
};

typedef Projectile *pProjectile;

#endif