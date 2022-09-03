#ifndef SNOWBALL_HPP
#define SNOWBALL_HPP

#include "../projectile.hpp"

const int snowball_states=1;
const int snowball_up_index=0;
const int snowball_down_index=1;
const int snowball_left_index=2;
const int snowball_right_index=3;

const int snowball_horizontal_height=2;
const int snowball_horizontal_width=2;

const int snowball_vertical_height=2;
const int snowball_vertical_width=2;

const char snowball_right[ANIMATION_HEIGHT][ANIMATION_WIDTH]=
{
    {'*', '*'},
    {'*', '*'}
  
};

const char snowball_left[ANIMATION_HEIGHT][ANIMATION_WIDTH]=
{
    {'*', '*'},
    {'*', '*'}
  
};

const char snowball_up[ANIMATION_HEIGHT][ANIMATION_WIDTH]=
{
    {'*', '*'},
    {'*', '*'}
  
};

const char snowball_down[ANIMATION_HEIGHT][ANIMATION_WIDTH]=
{
    {'*', '*'},
    {'*', '*'}
  
};

class Snowball :public Projectile{
    protected:

    private:

    public:
        Snowball (int fisico, int magico, char dir, int shooter);
};

#endif