#ifndef WITCH_ROD_HPP
#define WITCH_ROD_HPP

#include "../equipment/rod.hpp"
#include "../projectiles/spell.hpp"

const int witch_rod_up_index=0;
const int witch_rod_down_index=1;
const int witch_rod_left_index=2;
const int witch_rod_right_index=3;
const int witch_rod_attack_up_index=4;
const int witch_rod_attack_down_index=5;
const int witch_rod_attack_left_index=6;
const int witch_rod_attack_right_index=7;


const int witch_rod_movement_states=1;
const int witch_rod_attack_states=3;

const int witch_rod_height=8;
const int witch_rod_width=12;

const int witch_x_coordinate=3;
const int witch_y_coordinate=2;

const char witch_rod_up[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=8 width=12

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', 'o', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' '},
    {' ',' ', ' ' ,' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
	}
};


const char witch_rod_left[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=8 width=12

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', 'o' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', '|' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ',' ', '|' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', '|' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
	}
};

const char witch_rod_right[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=8 width=12

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', 'o', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' '},
    {' ',' ', ' ' ,' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
	}
};



const char witch_rod_down[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=8 width=12

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' '},
    {' ',' ', ' ' ,' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', 'o', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
	}
};

const char witch_rod_attack_right[3][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=8 width=12

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', '*', ' ', '*', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', '*', ' ', 'o', ' ', '*', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' '},
    {' ',' ', ' ' ,' ', ' ', ' ', ' ', '/', '|', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
	},

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', '*', 'o', '*', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' '},
    {' ',' ', ' ' ,' ', ' ', ' ', ' ', '/', '|', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
	},
{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', 'o', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' '},
    {' ',' ', ' ' ,' ', ' ', ' ', ' ', '/', '|', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
	}

};


const char witch_rod_attack_left[3][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=8 width=12

{   {'*',' ', '*' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{'*','o', ' ' ,'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ','|', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ','|', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ','|', '\\' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
	},

{   {' ','*', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{'*','o', '*' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ','|', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ','|', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ','|', '\\' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
	},
{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ','o', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ','|', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ','|', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ','|', '\\' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
	}

};


const char witch_rod_attack_down[3][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=8 width=12

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' '},
    {' ',' ', ' ' ,' ', ' ', ' ', ' ', '\\', '|', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', '*', ' ', 'o', ' ', '*', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', '*', ' ', '*', ' ', ' '}
	},

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' '},
    {' ',' ', ' ' ,' ', ' ', ' ', ' ', '\\', '|', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', '*', 'o', '*', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' '}
	},
{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' '},
    {' ',' ', ' ' ,' ', ' ', ' ', ' ', '\\', '|', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', 'o', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
	}

};


const char witch_rod_attack_up[3][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=8 width=12

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', '*', ' ', '*', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', '*', ' ', 'o', ' ', '*', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' '},
    {' ',' ', ' ' ,' ', ' ', ' ', ' ', '/', '|', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
	},

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', '*', 'o', '*', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' '},
    {' ',' ', ' ' ,' ', ' ', ' ', ' ', '/', '|', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
	},
{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', 'o', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' '},
    {' ',' ', ' ' ,' ', ' ', ' ', ' ', '/', '|', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
	}

};

class Witch_Rod: public Rod{
	protected:
		Spell spell;
    public:
        Witch_Rod();

		void shoot();

};

typedef Witch_Rod* pWitch_rod;



#endif