#ifndef PLAYER_H
#define PLAYER_H

#include "character.hpp"

const int idle_index = 0;
const int move_right_index = 1;
const int move_left_index = 2;
const int move_up_index = 3;
const int move_down_index = 4;
const int move_right_states = 2;
const int move_up_states = 2;
const int move_down_states = 2;
const int move_left_states = 2;
const int p_width = 3;
const int p_height = 3;
const char idle[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
	{{' ', 'A' , ' '},
	{'-', 'O', '-' },
	{'/', ' ', '\\'}} //se sono di più si mette qua la virgola e poi si rifà {}
};
const char move_right[move_right_states][ANIMATION_HEIGHT][ANIMATION_WIDTH]{
{   {' ', 'A' , ' '},
	{'-', 'O', '-' },
	{'/', '|', ' '}
	},

{   {' ', 'A' , '/'},
	{'-', 'O', ' '},
	{'/', '|', ' '}
	}
};
const char move_left[move_left_states][ANIMATION_HEIGHT][ANIMATION_WIDTH]{
{   {' ', 'A' , ' ' },
	{'-', 'O',  '-' },
	{' ', '|',  '\\'}
	},

{   {'\\', 'A' , ' '},
	{' ',  'O',  '-'},
	{' ',  '|', '\\'}
	}
};
const char move_up[move_up_states][ANIMATION_HEIGHT][ANIMATION_WIDTH]{
{   {' ', 'A' , ' ' },
	{'-', 'O',  '-' },
	{'/', ' ',  '\\'}
	},

{   {' ',  'A' , ' '},
	{' ',  'O',  ' '},
	{'/',  '|', '\\'}
	}
};	
const char move_down[move_down_states][ANIMATION_HEIGHT][ANIMATION_WIDTH]{
{   {' ', 'A' , ' ' },
	{'-', 'O',  '-' },
	{'/ ',' ',  '\\'}
	},

{   {'\\', 'A' , ' /'},
	{' ',  'O',  ' '},
	{'/ ', ' ', '\\'}
	}
};



const int p_max_health;
//il suo attacco dipende dall'arma


class Player : public Character {
	private:
	
	public:
		Player();
	
		void move(int input);

};




#endif