#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include "../enemy.hpp"
#include "../enemy_weapons/zombie_hands.hpp"
#include "../equipment/armor.hpp"

const int zombie_points=20;

const int zombie_width=4;
const int zombie_height=3;
const int zombie_depth=1;

const int zombie_idle_index=0;
const int zombie_move_up_index=1;
const int zombie_move_down_index=2;
const int zombie_move_left_index=3;
const int zombie_move_right_index=4;

const int zombie_idle_states=1;
const int zombie_move_up_states=2;
const int zombie_move_down_states=2;
const int zombie_move_left_states=2;
const int zombie_move_right_states=2;

const char zombie_idle[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{' ', '(', ')', ' '},
	{'/', '|', '|', '\\'},
	{'/', ' ', ' ', '\\'}
	
	}
};

const char zombie_move_up[2][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{' ', '(', ')', ' '},
	{'<', '|', '|', '>'},
	{'/', ' ', ' ', '\\'}
	
	},

{
	{' ', '(', ')', ' '},
	{'-', '|', '|', '-'},
	{'/', ' ', ' ', '\\'}
	
	}
};

const char zombie_move_down[2][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{' ', '(', ')', ' '},
	{'<', '|', '|', '>'},
	{'/', ' ', ' ', '\\'}
	
	},

{
	{' ', '(', ')', ' '},
	{'-', '|', '|', '-'},
	{'/', ' ', ' ', '\\'}
	
	}
};

const char zombie_move_left[2][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{' ', '(', ')', ' '},
	{'=', '|', '|', ' '},
	{'/', ' ', ' ', '\\'}
	
	},

{
	{' ', '(', ')', ' '},
	{'=', '|', '|', ' '},
	{'/', ' ', '|', ' '}
	
	}
};


const char zombie_move_right[2][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{' ', '(', ')', ' '},
	{' ', '|', '|', '='},
	{'/', ' ', ' ', '\\'}
	
	},

{
	{' ', '(', ')', ' '},
	{' ', '|', '|', '='},
	{' ', '|', ' ', '\\'}
	
	}
};


class Zombie: public Enemy{
    public:
		pZombie_hands zombie_hands;
		pArmor armatura; 
        Zombie();
        Zombie(pCharacter p);
};

typedef Zombie* pZombie;

#endif