#ifndef ARROW_HPP
#define ARROW_HPP

#include "main/projectile.hpp"

const int arrow_states=1;
const int arrow_up_index=0;
const int arrow_down_index=1;
const int arrow_left_index=2;
const int arrow_right_index=3;

const int arrow_horizontal_height=2;
const int arrow_horizontal_width=3;
const int arrow_horizontal_depth=1;
const int arrow_vertical_height=4;
const int arrow_vertical_width=1;
const int arrow_vertical_depth=3;

const char arrow_right[ANIMATION_HEIGHT][ANIMATION_WIDTH]=
{ 
   {'-', '-', '>'} ,
   {' ', ' ', ' '}
   
};

const char arrow_left[ANIMATION_HEIGHT][ANIMATION_WIDTH]=
{ 
   {'<', '-', '-'},
   {' ', ' ', ' '}
};

const char arrow_up[ANIMATION_HEIGHT][ANIMATION_WIDTH]=
{ 
   {'^'},
   {'|'},
   {'|'},
   {' '}
};

const char arrow_down[ANIMATION_HEIGHT][ANIMATION_WIDTH]=
{   
   {'|'},
   {'|'},
   {'v'},
   {' '}
};

class Arrow:public Projectile{
    protected:

    private:

    public:
        Arrow (int fisico, int magico, char dir, int shooter);
};

typedef Arrow* pArrow;

#endif