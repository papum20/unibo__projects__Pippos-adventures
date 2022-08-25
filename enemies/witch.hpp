#ifndef WITCH_HPP
#define WITCH_HPP

#include "enemy.hpp"

const char witcher_idle[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{'_', ')', '\\', '_'},
	{' ', '/', ' ', '\\'},
    {'(', '_', '"', ')'},
	{'/', '_', '_', '\\'}

	}
};

const char witcher_left[2][ANIMATION_HEIGHT][ANIMATION_WIDTH]={

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

const char witcher_right[2][ANIMATION_HEIGHT][ANIMATION_WIDTH]={

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

const char witcher_up[2][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
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

const char witcher_down[2][ANIMATION_HEIGHT][ANIMATION_WIDTH]={

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
        Bastone_magico witch_rod;
        Witch();

};

typedef Witch* pWitch;

#endif