#ifndef SNOWBALL_HPP
#define SNOWBALL_HPP

#include "projectile.hpp"

const int snowball_states=1;
const int snowball_up_index=0;
const int snowball_down_index=1;
const int snowball_left_index=2;
const int snowball_right_index=3;

const int snowball_height=1;
const int snowball_width=1;

const char snowball_right[snowball_height][snowball_width]=
{
    {'*'}
  
};

const char snowball_left[snowball_height][snowball_width]=
{
    {'*'}
  
};

const char snowball_up[snowball_height][snowball_width]=
{
    {'*'}
  
};

const char snowball_down[snowball_height][snowball_width]=
{
    {'*'}
  
};

class Snowball :public Projectile{
    protected:

    private:

    public:
        Snowball (Weapon w);
};

#endif