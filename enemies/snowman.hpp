#ifndef SNOWMAN_HPP
#define SNOWMAN_HPP

#include "enemy.hpp"
#include "snowman_hands.hpp"

const int snowman_height=4;
const int snowman_width=9;

const int snowman_points=50;

const int snowman_idle_index=0;
const int snowman_move_up_index=1;
const int snowman_move_down_index=2;
const int snowman_move_left_index=3;
const int snowman_move_right_index=4;

const int snowman_idle_states=1;
const int snowman_move_up_states=2;
const int snowman_move_down_states=2;
const int snowman_move_left_states=2;
const int snowman_move_right_states=2;

const char snowman_idle[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{' ',' ', '_' ,'[', '_', ']', '_', ' ', ' '},
	{' ',' ', ' ' ,'(', '"', ')', ' ', ' ', ' '},
	{'-','-', '(' ,' ', ':', ' ', ')', '-', '-'},
    {' ','(', '_' ,'_', ':', '_', '_', ')', ' '}
	
	}
};

const char snowman_move_up[2][ANIMATION_HEIGHT][ANIMATION_WIDTH]={

{
	{' ',' ', '_' ,'[', '_', ']', '_', ' ', ' '},
	{' ',' ', ' ' ,'(', ' ', ')', ' ', ' ', ' '},
	{'-','-', '(' ,' ', ':', ' ', ')', '-', '-'},
    {' ','(', '_' ,'_', ':', '_', '_', ')', ' '}

	},
{
	{' ',' ', '_' ,'[', '_', ']', '_', ' ', ' '},
	{' ',' ', ' ' ,'(', ' ', ')', ' ', ' ', ' '},
	{' ','/', '(' ,' ', ':', ' ', ')', '\\', ' '},
    {'/','(', '_' ,'_', ':', '_', '_', ')', '\\'}

	}
};

const char snowman_move_down[2][ANIMATION_HEIGHT][ANIMATION_WIDTH]={

{
	{' ',' ', '_' ,'[', '_', ']', '_', ' ', ' '},
	{' ',' ', ' ' ,'(', '"', ')', ' ', ' ', ' '},
	{'-','-', '(' ,' ', ':', ' ', ')', '-', '-'},
    {' ','(', '_' ,'_', ':', '_', '_', ')', ' '}

	},
{
	{' ',' ', '_' ,'[', '_', ']', '_', ' ', ' '},
	{'\\',' ', ' ' ,'(', '"', ')', ' ', ' ', '/'},
	{' ','\\', '(' ,' ', ':', ' ', ')', '/', ' '},
    {' ','(', '_' ,'_', ':', '_', '_', ')', ' '}

	}
};

const char snowman_move_left[2][ANIMATION_HEIGHT][ANIMATION_WIDTH]={

{
	{' ',' ', '_' ,'[', '_', ']', '_', ' ', ' '},
	{' ',' ', ' ' ,'(', '.', ')', ' ', ' ', ' '},
	{'-','-', '(' ,' ', ':', ' ', ')', ' ', ' '},
    {' ','(', '_' ,'_', ':', '_', '_', ')', ' '}

	},
{
	{' ',' ', '_' ,'[', '_', ']', '_', ' ', ' '},
	{'\\',' ', ' ' ,'(', '.', ')', ' ', ' ', ' '},
	{' ','\\', '(' ,' ', ':', ' ', ')', ' ', ' '},
    {' ','(', '_' ,'_', ':', '_', '_', ')', ' '}

	}
};

const char snowman_move_right[2][ANIMATION_HEIGHT][ANIMATION_WIDTH]={

{
	{' ',' ', '_' ,'[', '_', ']', '_', ' ', ' '},
	{' ',' ', ' ' ,'(', '.', ')', ' ', ' ', ' '},
	{' ',' ', '(' ,' ', ':', ' ', ')', '-', '-'},
    {' ','(', '_' ,'_', ':', '_', '_', ')', ' '}

	},
{
	{' ',' ', '_' ,'[', '_', ']', '_', ' ', ' '},
	{' ',' ', ' ' ,'(', '.', ')', ' ', ' ', '/'},
	{' ',' ', '(' ,' ', ':', ' ', ')', '/', ' '},
    {' ','(', '_' ,'_', ':', '_', '_', ')', ' '}

	}
};

class Snowman: public Enemy{
    public:
		pSnowman_hands snowman_hands;
		pArmor armatura;
		pNecklace collana;
		pBoots stivali;
        Snowman();
};

typedef Snowman* pSnowman;

#endif