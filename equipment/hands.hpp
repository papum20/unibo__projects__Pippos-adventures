#ifndef HANDS_HPP
#define HANDS_HPP

#include "../weapon.hpp"


class Hands: public Weapon {
    private:

    protected:

    public:
        Hands();
        Hands(int d_f, float d_m, const char rar[]);

};

#endif