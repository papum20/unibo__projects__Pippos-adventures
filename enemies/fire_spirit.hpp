#ifndef FIRE_SPIRIT_HPP
#define FIRE_SPIRIT_HPP

#include "../enemy.hpp"
#include "../enemy_weapons/fire_spirit_hands.hpp"

const int fire_spirit_points=20;

const int fire_spirit_width=4;
const int fire_spirit_height=5;

const int fire_spirit_idle_index=0;
const int fire_spirit_move_up_index=1;
const int fire_spirit_move_down_index=2;
const int fire_spirit_move_left_index=3;
const int fire_spirit_move_right_index=4;

const int fire_spirit_idle_states=1;
const int fire_spirit_move_up_states=3;
const int fire_spirit_move_down_states=3;
const int fire_spirit_move_left_states=3;
const int fire_spirit_move_right_states=3;

const char fire_spirit_idle[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{char(39), ' ', ' ', ' '},
	{'.', ' ', char(39), ' '},
	{'_', char(39), char(39), '_'},
	{' ', ' ', ' ', ' '},
	{',', ' ', ' ', ','}
	
	}
};

const char fire_spirit_move_right[3][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{' ', ' ', ' ', char(39)},
	{char(39), ' ', ' ', ','},
	{'_', ')', '"', '_'},
	{' ', ' ', ' ', ' '},
	{' ', char(39), char(39), ' '}
	
	},

{
	{char(39), ' ', ' ', ' '},
	{'.', ' ', ' ', char(39)},
	{' ', ')', '"', ' '},
	{'/', ' ', ' ', '\\'},
	{',', ' ', ' ', ','}
	
	},

{
	{'.', ' ', ' ', '.'},
	{' ', ' ', ' ', '('},
	{' ', ')', '"', ' '},
	{'(', ' ', ' ', ')'},
	{' ', char(39), char(39), ' '}
	
	}
};




const char fire_spirit_move_left[3][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{' ', ' ', ' ', char(39)},
	{char(39), ' ', ' ', ' '},
	{'_', '"', '(', '_'},
	{' ', ' ', ' ', ' '},
	{' ', char(39), char(39), ' '}
	
	},

{
	{char(39), ' ', ' ', ' '},
	{'.', ' ', char(39), ' '},
	{' ', '"', '(', ' '},
	{'/', ' ', ' ', '\\'},
	{',', ' ', ' ', ','}
	
	},

{
	{' ', ' ', ' ', '.'},
	{')', ' ', ' ', ' '},
	{' ', '"', '(', ' '},
	{'(', ' ', ' ', ')'},
	{' ', char(39), char(39), ' '}
	
	}
};

const char fire_spirit_move_up[3][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{' ', ' ', ' ', char(39)},
	{char(39), ' ', ' ', ','},
	{'\\', char(39), char(39), '/'},
	{' ', ' ', ' ', ' '},
	{' ', char(39), char(39), ' '}
	
	},

{
	{' ', char(39), ' ', ' '},
	{char(39), ' ', '.', ' '},
	{' ', char(39), char(39), ' '},
	{'/', ' ', ' ', '\\'},
	{',', ' ', ' ', ','}
	
	},

{
	{' ', char(39), ' ', ' '},
	{'.', ' ', char(39), ' '},
	{' ', char(39), char(39), ' '},
	{'/', ' ', ' ', '\\'},
	{' ', char(39), char(39), ' '}
	
	}
};


const char fire_spirit_move_down[3][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{' ', ' ', ' ', char(39)},
	{char(39), ' ', ' ', ','},
	{'\\', char(39), char(39), '/'},
	{' ', ' ', ' ', ' '},
	{' ', char(39), char(39), ' '}
	
	},

{
	{' ', char(39), ' ', ' '},
	{char(39), ' ', '.', ' '},
	{' ', char(39), char(39), ' '},
	{'/', ' ', ' ', '\\'},
	{',', ' ', ' ', ','}
	
	},

{
	{' ', char(39), ' ', ' '},
	{'.', ' ', char(39), ' '},
	{' ', char(39), char(39), ' '},
	{'/', ' ', ' ', '\\'},
	{' ', char(39), char(39), ' '}
	
	}
};


class Fire_spirit: public Enemy{
    public:
		pFS_Hands fire_spirit_hands;
		pNecklace collana;
        Fire_spirit();
        Fire_spirit(pCharacter p);
};

typedef Fire_spirit* pFire_spirit;

#endif