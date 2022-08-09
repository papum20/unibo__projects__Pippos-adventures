#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP
#include "physical.hpp"

Class Projectile: public Physical{
    protected:
        int danno;
        int width;
        int height;
        bool enemy;
        bool player;
    public:
        Projectile (int d, int w, int h, p_Animation animazioni[], bool e, bool p);
};

#endif