#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "character.hpp"
#include "inputmanager.hpp"
#include "equipment/shield.hpp"

const int player_idle_index = 0;
const int player_move_right_index = 1;
const int player_move_left_index = 2;
const int player_move_up_index = 3;
const int player_move_down_index = 4;
const int player_dash_up_index = 5;
const int player_dash_down_index = 6;
const int player_dash_left_index = 7;
const int player_dash_right_index = 8;

const int player_idle_states = 1;
const int player_move_right_states = 2;
const int player_move_up_states = 2;
const int player_move_down_states = 2;
const int player_move_left_states = 2;
const int player_dash_up_states = 1;
const int player_dash_down_states = 1;
const int player_dash_left_states = 1;
const int player_dash_right_states = 1;

const int p_width = 3;
const int p_height = 3;

const int w_attack_height=8;
const int w_attack_width=9;

const char idle[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
	{{' ', 'o' , ' '},
	{'/', '|', '\\' },
	{'/', ' ', '\\'}} //se sono di più si mette qua la virgola e poi si rifà {}
};
const char move_right[player_move_right_states][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{   {' ', 'o' , ' '},
	{'/', '|', '-' },
	{'/', '|', ' '}
	},

{   {' ', 'o' , '/'},
	{'/', '|', ' '},
	{'/', '|', ' '}
	}
};
const char move_left[player_move_left_states][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{   {' ', 'o' , ' ' },
	{'-', '|',  '\\' },
	{' ', '|',  '\\'}
	},

{   {'\\', 'o' , ' '},
	{' ',  '|',  '\\'},
	{' ',  '|', '\\'}
	}
};
const char move_up[player_move_up_states][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{   {' ', 'o' , ' ' },
	{'/', '|',  '\\' },
	{'/', ' ',  '\\'}
	},

{   {'\\',  'o' , '/'},
	{' ',  '|',  ' '},
	{'/',  ' ', '\\'}
	}
};	
const char move_down[player_move_down_states][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{   {' ', 'o' , ' ' },
	{'/', '|',  '\\' },
	{'/',' ',  '\\'}
	},

{   {'\\', 'o' , '/'},
	{' ',  '|',  ' '},
	{'/', ' ', '\\'}
	}
};
const char dash_left[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
	{{'\\', 'o', '='},
	{' ', '|', '=' },
	{' ', '|', '\\'}} 
};
const char dash_right[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
	{{'=', 'o', '/'},
	{'=', '|', ' ' },
	{'/', '|', ' '}} 
};
const char dash_up[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
	{{'\\', 'o', '/'},
	{' ', '|', ' ' },
	{'|', ' ', '|'}} 
};
const char dash_down[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
	{{'|', '|', '|'},
	{' ', '|', ' ' },
	{'/', 'o', '\\'}} 
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
		int points;

		pArtifact artifacts[MAX_ARTIFACTS];
		int curr_artifact;
		pInputManager in_manager;
		//Menu menu;
	public:
		int n_hearts;		
		int n_keys;
		
		Player(pInputManager in);
	
		void update(pMap map);

		void modify_lifes (int delta);

		void collect_item(pMap mappa);

		void add_item(pWeapon w);
		void add_item(pItem_def w);
		void add_item(pArtifact w);

		void change_helm(pHelm h);
		void change_weapon(pWeapon w);
		void change_necklace (pNecklace n);
		void change_armor (pArmor a);
		void change_boots (pBoots b);
		void change_shield (pShield s);


		void change_points(int delta);
		pDoor usedDoor();				//porta usata, NULL se non sta usando una porta
		
};

typedef Player *pPlayer;


#include "door.hpp"
#include "chest.hpp"


#endif
