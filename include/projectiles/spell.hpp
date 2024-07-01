#ifndef SPELL_HPP
#define SPELL_HPP

#include "main/projectile.hpp"
//#include "equipment/player_rod.hpp"
//#include "main/witch_rod.hpp"

const int spell_states=1;
const int spell_up_index=0;
const int spell_down_index=1;
const int spell_left_index=2;
const int spell_right_index=3;

const int spell_horizontal_height=2;
const int spell_horizontal_width=2;

const int spell_vertical_height=2;
const int spell_vertical_width=2;

const char spell_right[ANIMATION_HEIGHT][ANIMATION_WIDTH]=
{
    {'/', '\\'},
    {'\\', '/'}
  
};

const char spell_left[ANIMATION_HEIGHT][ANIMATION_WIDTH]=
{
    {'/', '\\'},
    {'\\', '/'}
  
};

const char spell_up[ANIMATION_HEIGHT][ANIMATION_WIDTH]=
{
    {'/', '\\'},
    {'\\', '/'}
  
};

const char spell_down[ANIMATION_HEIGHT][ANIMATION_WIDTH]=
{
    {'/', '\\'},
    {'\\', '/'}
  
};

class Spell :public Projectile{
    protected:

    private:

    public:
        //Spell (pWeapon w);
        Spell (int fisico, int magico, char dir, int shooter);
};

typedef Spell* pSpell;

#endif