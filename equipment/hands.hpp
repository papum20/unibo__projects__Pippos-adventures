#ifndef HANDS_HPP
#define HANDS_HPP

#include "weapon.hpp"


class Hands: public Weapon {
    private:

    protected:

    public:
        Hands(int d_f, float d_m, const char rar[], const char n[], const char desc[]);

};

#endif