#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP
#include "physical.hpp"

Class Projectile: public Physical{
    protected:
        int danno;
        int width;
        int height;
    public:
        Projectile (int d, int w, int h, p_Animation animazioni[]);
};

#endif