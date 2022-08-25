#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include "enemy.hpp"

const char zombie_idle[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{' ', '(', ')', ' '},
	{'/', '|', '|', '\\'},
	{'/', ' ', ' ', '\\'}
	
	}
};

const char zombie_up[2][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
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

const char zombie_down[2][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
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

const char zombie_left[2][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
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


const char zombie_right[2][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
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
        Zombie();
};

typedef Zombie* pZombie;

#endif