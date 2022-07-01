#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "character.hpp"

const int idle_index = 0;
const int move_right_index = 1;
const int move_left_index = 2;
const int move_up_index = 3;
const int move_down_index = 4;
const int dash_up_index = 5;
const int dash_down_index = 6;
const int dash_left_index = 7;
const int dash_right_index = 8;

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
const char move_right[move_right_states][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{   {' ', 'A' , ' '},
	{'-', 'O', '-' },
	{'/', '|', ' '}
	},

{   {' ', 'A' , '/'},
	{'-', 'O', ' '},
	{'/', '|', ' '}
	}
};
const char move_left[move_left_states][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{   {' ', 'A' , ' ' },
	{'-', 'O',  '-' },
	{' ', '|',  '\\'}
	},

{   {'\\', 'A' , ' '},
	{' ',  'O',  '-'},
	{' ',  '|', '\\'}
	}
};
const char move_up[move_up_states][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{   {' ', 'A' , ' ' },
	{'-', 'O',  '-' },
	{'/', ' ',  '\\'}
	},

{   {' ',  'A' , ' '},
	{' ',  'O',  ' '},
	{'/',  '|', '\\'}
	}
};	
const char move_down[move_down_states][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{   {' ', 'A' , ' ' },
	{'-', 'O',  '-' },
	{'/',' ',  '\\'}
	},

{   {'\\', 'A' , '/'},
	{' ',  'O',  ' '},
	{'/', ' ', '\\'}
	}
};
const char dash_left[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
	{{'\\', 'A', '='},
	{' ', 'O', '=' },
	{' ', '|', '\\'}} 
};
const char dash_right[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
	{{'=', 'A', '/'},
	{'=', 'O', ' ' },
	{'/', '|', ' '}} 
};
const char dash_up[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
	{{'\\', 'A', '/'},
	{' ', 'O', ' ' },
	{'|', '|', '|'}} 
};
const char dash_down[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
	{{'|', '|', '|'},
	{' ', 'O', ' ' },
	{'/', 'A', '\\'}} 
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