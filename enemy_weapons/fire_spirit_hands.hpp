#ifndef FIRE_SPIRIT_HANDS_HPP
#define FIRE_SPIRIT_HANDS_HPP

#include "hands.hpp"
#include "fireball.hpp"

const int fire_spirit_hands_movement_states=1;
const int fire_spirit_hands_attack_states=3;

const int fire_spirit_hands_up_index=0;
const int fire_spirit_hands_down_index=1;
const int fire_spirit_hands_left_index=2;
const int fire_spirit_hands_right_index=3;
const int fire_spirit_hands_attack_up_index=4;
const int fire_spirit_hands_attack_down_index=5;
const int fire_spirit_hands_attack_left_index=6;
const int fire_spirit_hands_attack_right_index=7;

const int fire_spirit_hands_height=5;
const int fire_spirit_hands_width=4;

const char fire_spirit_hands_up[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={

{   {' ',' ', ' ' ,' '},
	{' ',' ', ' ' ,' '},
	{' ',' ', ' ' ,' '},
	{' ',' ', ' ' ,' '},
    {' ',' ', ' ' ,' '}
	}
};

const char fire_spirit_hands_down[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={

{   {' ',' ', ' ' ,' '},
	{' ',' ', ' ' ,' '},
	{' ',' ', ' ' ,' '},
	{' ',' ', ' ' ,' '},
    {' ',' ', ' ' ,' '}
	}
};

const char fire_spirit_hands_left[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={

{   {' ',' ', ' ' ,' '},
	{' ',' ', ' ' ,' '},
	{' ',' ', ' ' ,' '},
	{' ',' ', ' ' ,' '},
    {' ',' ', ' ' ,' '}
	}
};


const char fire_spirit_hands_right[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={

{   {' ',' ', ' ' ,' '},
	{' ',' ', ' ' ,' '},
	{' ',' ', ' ' ,' '},
	{' ',' ', ' ' ,' '},
    {' ',' ', ' ' ,' '}
	}
};

const char fire_spirit_hands_attack_right[3][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' '},
	{'\\', ' ', ' ', '/'},
	{' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' '}
	
	},

{
	{' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' '},
	{'_', ' ', ' ', '_'},
	{'m', ' ', ' ', 'm'},
	{' ', ' ', ' ', ' '}
	
	},

{
	{' ', ' ', ' ', '.'},
	{' ', ' ', ' ', ' '},
	{'m', ' ', ' ', 'm'},
	{'/', ' ', ' ', '\\'},
	{' ', ' ', ' ', ' '}
	
	}
};

const char fire_spirit_hands_attack_left[3][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' '},
	{'\\', ' ', ' ', '/'},
	{' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' '}
	
	},

{
	{' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' '},
	{'_', ' ', ' ', '_'},
	{'m', ' ', ' ', 'm'},
	{' ', ' ', ' ', ' '}
	
	},

{
	{' ', ' ', ' ', '.'},
	{' ', ' ', ' ', ' '},
	{'m', ' ', ' ', 'm'},
	{'/', ' ', ' ', '\\'},
	{' ', ' ', ' ', ' '}
	
	}
};

const char fire_spirit_hands_attack_up[3][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' '},
	{'\\', ' ', ' ', '/'},
	{' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' '}
	
	},

{
	{' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' '},
	{'_', ' ', ' ', '_'},
	{'m', ' ', ' ', 'm'},
	{' ', ' ', ' ', ' '}
	
	},

{
	{' ', ' ', ' ', '.'},
	{' ', ' ', ' ', ' '},
	{'m', ' ', ' ', 'm'},
	{'/', ' ', ' ', '\\'},
	{' ', ' ', ' ', ' '}
	
	}
};

const char fire_spirit_hands_attack_down[3][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' '},
	{'\\', ' ', ' ', '/'},
	{' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' '}
	
	},

{
	{' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' '},
	{'_', ' ', ' ', '_'},
	{'m', ' ', ' ', 'm'},
	{' ', ' ', ' ', ' '}
	
	},

{
	{' ', ' ', ' ', '.'},
	{' ', ' ', ' ', ' '},
	{'m', ' ', ' ', 'm'},
	{'/', ' ', ' ', '\\'},
	{' ', ' ', ' ', ' '}
	
	}
};

class Fire_spirit_hands: public Hands{
	protected:
		Fireball fireball;
    public:
        Fire_spirit_hands();

};

typedef Fire_spirit_hands* pFS_Hands;

#endif