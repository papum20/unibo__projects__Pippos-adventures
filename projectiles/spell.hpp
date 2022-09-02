#ifndef SPELL_HPP
#define SPELL_HPP

#include "../projectile.hpp"

const int spell_states=1;
const int spell_up_index=0;
const int spell_down_index=1;
const int spell_left_index=2;
const int spell_right_index=3;

const int spell_height=2;
const int spell_width=2;

const char spell_right[spell_height][spell_width]=
{
    {'/', '\\'},
    {'\\', '/'}
  
};

const char spell_left[spell_height][spell_width]=
{
    {'/', '\\'},
    {'\\', '/'}
  
};

const char spell_up[spell_height][spell_width]=
{
    {'/', '\\'},
    {'\\', '/'}
  
};

const char spell_down[spell_height][spell_width]=
{
    {'/', '\\'},
    {'\\', '/'}
  
};

class Spell :public Projectile{
    protected:

    private:

    public:
        Spell (Weapon w);
};

#endif