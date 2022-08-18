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

const int idle_states = 1;
const int move_right_states = 2;
const int move_up_states = 2;
const int move_down_states = 2;
const int move_left_states = 2;
const int dash_up_states = 1;
const int dash_down_states = 1;
const int dash_left_states = 1;
const int dash_right_states = 1;
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



const int max_lifes=5;
const int start_lifes=3;
const int p_max_health = 100;
const int p_max_stamina=50;
//il suo attacco dipende dall'arma

//timer
const int timer_idle = 0;
const int timer_dash_animation = 1;
const int timer_dash_trail = 2;
const int timer_dash_countdown = 3;
//

const int dash_button = (int)'d';
const int n_dash_move = 5; //numero di caselle dello spostamento del dash
const int dash_stamina = 10; //numero di stamina che serve per fare la scivolata
const int mv_up=KEY_UP;          //generalizzazione del movimento
const int mv_down=KEY_DOWN;
const int mv_left=KEY_LEFT;
const int mv_right=KEY_RIGHT;

const int MAX_ARTIFACTS=10;

class Player : public Character {
	private:
	protected:
		int n_hearts;		

		pArtifact artifacts[MAX_ARTIFACTS];
		int curr_artifact;

	public:
		Player();
	
		void update(pInanimate map[], pCharacter characters[]);

		void modify_lifes (int delta);

		void collect_item();

		void add_item(pWeapon w);
		void add_item(pItem_def w);
		void add_item(pArtifact w);
		
};

typedef Player *pPlayer;



#endif