#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "animate.hpp"
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
        void setPosition (Coordinate shooter_pos, Coordinate shooter_size);
};

typedef Projectile *pProjectile;


#endif