#ifndef ARROW_HPP
#define ARROW_HPP

#include "../projectile.hpp"

const int arrow_states=1;
const int arrow_up_index=0;
const int arrow_down_index=1;
const int arrow_left_index=2;
const int arrow_right_index=3;

const int arrow_horizontal_height=1;
const int arrow_horizontal_width=3;
const int arrow_vertical_height=3;
const int arrow_vertical_width=1;

const char arrow_right[arrow_horizontal_height][arrow_horizontal_width]=
{ {
   {'-', '-', '>'} 
   }
};

const char arrow_left[arrow_horizontal_height][arrow_horizontal_width]=
{ {
   {'<', '-', '-'} 
  }
};

const char arrow_up[arrow_vertical_height][arrow_vertical_width]=
{ 
{  {'^'},
   {'|'},
   {'|'}
}
};

const char arrow_down[arrow_vertical_height][arrow_vertical_width]=
{ 
{  {'|'},
   {'|'},
   {'v'}
}
};

class Arrow:public Projectile{
    protected:

    private:

    public:
        Arrow (Weapon w);
};

#endif