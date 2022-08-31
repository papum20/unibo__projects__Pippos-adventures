#ifndef FIREBALL_HPP
#define FIREBALL_HPP

#include "projectile.hpp"

const int fireball_states=1;
const int fireball_up_index=0;
const int fireball_down_index=1;
const int fireball_left_index=2;
const int fireball_right_index=3;

const int fireball_horizontal_height=1;
const int fireball_horizontal_width=4;

const int fireball_vertical_height=4;
const int fireball_vertical_width=1;

const char fireball_right[fireball_horizontal_height][fireball_horizontal_width]=
{
    {'<', 'O', 'O', '>'}
  
};

const char fireball_left[fireball_horizontal_height][fireball_horizontal_width]=
{
    {'<', 'O', 'O', '>'}
  
};

const char fireball_up[fireball_vertical_height][fireball_vertical_width]=
{
    {'A'},
    {'O'},
    {'O'},
    {'V'}
};

const char fireball_down[fireball_vertical_height][fireball_vertical_width]=
{
    {'A'},
    {'O'},
    {'O'},
    {'V'}
};

class Fireball :public Projectile{
    protected:

    private:

    public:
        Fireball (Weapon w);
};

#endif