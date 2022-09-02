#ifndef WITCH_HPP
#define WITCH_HPP

#include "../enemy.hpp"
#include "../enemy_weapons/witch_rod.hpp"

const int witch_points=50;

const int witch_width=4;
const int witch_height=4;

const int witch_idle_index=0;
const int witch_move_up_index=1;
const int witch_move_down_index=2;
const int witch_move_left_index=3;
const int witch_move_right_index=4;

const int witch_idle_states=1;
const int witch_move_up_states=2;
const int witch_move_down_states=2;
const int witch_move_left_states=2;
const int witch_move_right_states=2;

const char witch_idle[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{'_', ')', '\\', '_'},
	{' ', '/', ' ', '\\'},
    {'(', '_', '"', ')'},
	{'/', '_', '_', '\\'}

	}
};

const char witch_move_left[2][ANIMATION_HEIGHT][ANIMATION_WIDTH]={

{
	{'_', '/', '(',' '},
	{'{', '\\', '\\',' '},
    {'-', '"', '_', ')'},
	{'/', '_', '_', '\\'},
	
	},

{
	{'_', '/', '(',' '},
	{'{', '\\', '\\',' '},
    {'\\', '"', '_', ')'},
	{'/', '_', '_', '\\'},
	
	}
};

const char witch_move_right[2][ANIMATION_HEIGHT][ANIMATION_WIDTH]={

{
	{'_', ')', '\\', '_'},
	{' ', '/', '/', '}'},
    {'(', '_', '"', '-'},
	{'/', '_', '_', '\\'}

	},

{
	{'_', ')', '\\', '_'},
	{' ', '/', '/', '}'},
    {'(', '_', '"', '/'},
	{'/', '_', '_', '\\'}

	}
};

const char witch_move_up[2][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{'_', ')', '\\', '_'},
	{' ', '/', ' ', '\\'},
    {'(', '_', '_', '-'},
	{'/', '_', '_', '\\'},

	},

{
	{'_', ')', '\\', '_'},
	{' ', '/', ' ', '\\'},
    {'(', '_', '_', '/'},
	{'/', '_', '_', '\\'},

	}
};

const char witch_move_down[2][ANIMATION_HEIGHT][ANIMATION_WIDTH]={

{
	{'_', ')', '\\', '_'},
	{' ', '/', ' ', '\\'},
    {'(', '_', '"', '-'},
	{'/', '_', '_', '\\'},

	},

{
	{'_', ')', '\\', '_'},
	{' ', '/', ' ', '\\'},
    {'(', '_', '"', '\\'},
	{'/', '_', '_', '\\'},

	}

};

class Witch: public Enemy{

    public:
        pWitch_rod witch_rod;
		pArmor armatura;
		pNecklace collana;
        Witch();

};

typedef Witch* pWitch;

#endif