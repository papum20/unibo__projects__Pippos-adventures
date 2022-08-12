#ifndef ARROW_HPP
#define ARROW_HPP

#include "projectile.hpp"

const int arrow_right_height=1;
const int arrow_right_width=3;
const int arrow_left_height=1;
const int arrow_left_width=3;

const int arrow_up_height=3;
const int arrow_up_width=3;
const int arrow_down_height=3;
const int arrow_down_width=3;

const char arrow_dx[][]={'-', '-', '>'};
const char arrow_sx[][]={'<', '-', '-'};
const char arrow_up[][]=
{ {'/', '|', '\\'},
  {' ', '|', ' '},
  {' ', '|', ' '}
};
const char arrow_down[][]=
{ {' ', '|', ' '},
  {' ', '|', ' '},
  {'\\', '|', '/'}
};

class Arrow:public Projectile{
    protected:

    private:

    public:
        Arrow (Weapon w, p_Animation animazioni[]);
};

#endif