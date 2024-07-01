#ifndef SPIDER_HPP
#define SPIDER_HPP

#include "main/enemy.hpp"
#include "enemy_weapons/spider_legs.hpp"

const int spider_points=40;

const int spider_width=7;
const int spider_height=4;
const int spider_depth=2;

const int spider_idle_index=0;
const int spider_move_up_index=1;
const int spider_move_down_index=2;
const int spider_move_left_index=3;
const int spider_move_right_index=4;

const int spider_idle_states=1;
const int spider_move_up_states=3;
const int spider_move_down_states=3;
const int spider_move_left_states=3;
const int spider_move_right_states=3;

const char spider_idle[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{'/','/',' ',' ',' ','\\','\\'},
	{'\\','\\','(',' ',')','/','/'},
	{'/','/',' ',' ',' ','\\','\\'},
	{'|','\\','_','_','_','/','|'}
	}

};

const char spider_move_left[3][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{' ',' ',' ',' ','_',' ',' '},
	{' ',' ',' ','(','_',')',' '},
	{' ','o','o','/',' ','\\',' '},
	{'/',' ',' ','|','<',' ','\\'}
	},
{
	{' ',' ',' ',' ','_',' ',' '},
	{' ',' ',' ','(','_',')',' '},
	{' ','o','o','/',' ','\\',' '},
	{'|',' ',' ','<','(','|',' '}
	},
{
	{' ',' ',' ',' ','_',' ',' '},
	{' ',' ',' ','(','_',')',' '},
	{' ','o','o','/',' ','\\',' '},
	{'/',' ',' ','(','|',')',' '}
	}

};
const char spider_move_right[3][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{' ',' ','_',' ',' ',' ',' '},
	{' ','(','_',')',' ',' ',' '},
	{' ','/',' ','\\','o','o',' '},
	{'/',' ',' ','|',' ',' ','\\'}
	},

{
	{' ',' ','_',' ',' ',' ',' '},
	{' ','(','_',')',' ',' ',' '},
	{' ','/',' ','\\','o','o',' '},
	{' ','|',')','>',' ',' ','|'}
	},
	{
	{' ',' ','_',' ',' ',' ',' '},
	{' ','(','_',')',' ',' ',' '},
	{' ','/',' ','\\','o','o',' '},
	{' ','(','|',')',' ',' ','\\'}
	}

};
const char spider_move_up[3][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{'/','/',' ',' ',' ','\\','\\'},
	{'\\','\\','(',' ',')','/','/'},
	{'/','/',' ',' ',' ','\\','\\'},
	{'\\','\\','_','_','_','/','/'}
	},
{
	{'|','/',' ',' ',' ','\\','|'},
	{'\\','\\','(',' ',')','/','/'},
	{'/','/',' ',' ',' ','\\','\\'},
	{'\\','\\','_','_','_','/','/'}
	},
{
	{'/','/',' ',' ',' ','\\','\\'},
	{'\\','\\','(',' ',')','/','/'},
	{'/','/',' ',' ',' ','\\','\\'},
	{'/','\\','_','_','_','/','\\'}
	}

};
const char spider_move_down[3][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{'/','/','-','-','-','\\','\\'},
	{'\\','\\',' ',' ',' ','/','/'},
	{'/','/','(',' ',')','\\','\\'},
	{'\\','\\',' ',' ',' ','/','/'}
	},
{
	{'|','/','-','-','-','\\','|'},
	{'\\','\\',' ',' ',' ','/','/'},
	{'/','/','(',' ',')','\\','\\'},
	{'\\','\\',' ',' ',' ','/','/'}
	},
{
	{'\\','/','-','-','-','\\','/'},
	{'\\','\\',' ',' ',' ','/','/'},
	{'/','/','(',' ',')','\\','\\'},
	{'\\','\\',' ',' ',' ','/','/'}
	}

};


class Spider: public Enemy{
    public:
        Spider();
        Spider(pCharacter p);
};

typedef Spider* pSpider;

#endif