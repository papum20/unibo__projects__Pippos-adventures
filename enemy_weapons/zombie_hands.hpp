#ifndef ZOMBIE_HANDS_HPP
#define ZOMBIE_HANDS_HPP

#include "../equipment/hands.hpp"

const int zombie_hands_movement_states=1;
const int zombie_hands_attack_states=2;

const int zombie_hands_up_index=0;
const int zombie_hands_down_index=1;
const int zombie_hands_left_index=2;
const int zombie_hands_right_index=3;
const int zombie_hands_attack_up_index=4;
const int zombie_hands_attack_down_index=5;
const int zombie_hands_attack_left_index=6;
const int zombie_hands_attack_right_index=7;

const int zombie_hands_height=5;
const int zombie_hands_width=6;

const int zombie_horizontal_attack_height=1;
const int zombie_vertical_attack_width=2;

const int zombie_delta_x_right=5;
const int zombie_delta_y_right=-2;

const int zombie_delta_x_left=0;
const int zombie_delta_y_left=-2;

const int zombie_delta_x_up=2;
const int zombie_delta_y_up=-4;

const int zombie_delta_x_down=2;
const int zombie_delta_y_down=0;

const char zombie_hands_up[1][WEAPON_ANIMATION_HEIGHT][WEAPON_ANIMATION_WIDTH]={
{
	{' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' '}
	}
};

const char zombie_hands_down[1][WEAPON_ANIMATION_HEIGHT][WEAPON_ANIMATION_WIDTH]={
{
	{' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' '}
	}
};

const char zombie_hands_left[1][WEAPON_ANIMATION_HEIGHT][WEAPON_ANIMATION_WIDTH]={
{
	{' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' '}
	}
};


const char zombie_hands_right[1][WEAPON_ANIMATION_HEIGHT][WEAPON_ANIMATION_WIDTH]={
{
	{' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' '}
	}
};

const char zombie_hands_attack_up[2][WEAPON_ANIMATION_HEIGHT][WEAPON_ANIMATION_WIDTH]={
{   {' ',' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' '},
	{' ','<', ' ', ' ', '>', ' '},
	{' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' '}
	
	},

{   {' ',' ', '|', '|', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' '},
	{' ','m', ' ', ' ', 'm', ' '},
	{' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' '}
	
	}
};


const char zombie_hands_attack_down[2][WEAPON_ANIMATION_HEIGHT][WEAPON_ANIMATION_WIDTH]={
{   {' ',' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' '},
	{' ','<', ' ', ' ', '>', ' '},
	{' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' '}
	
	},

{   {' ',' ', '|', '|', ' ', ' '},
	{' ',' ', 'm', 'm', ' ', ' '},
	{' ','m', '(', ')', 'm', ' '},
	{' ', ' ', '|', '|', ' ', ' '},
	{' ',' ', '|', '|', ' ', ' '}
	
	}
};

const char zombie_hands_attack_left[2][WEAPON_ANIMATION_HEIGHT][WEAPON_ANIMATION_WIDTH]={
{   {' ',' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' '}
	
	},

{   {' ',' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' '},
	{'=',' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' '}
	
	}
};

const char zombie_hands_attack_right[2][WEAPON_ANIMATION_HEIGHT][WEAPON_ANIMATION_WIDTH]={
{   {' ',' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' '}
	
	},

{   {' ',' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', '='},
	{' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' '}
	
	}
};

class Zombie_hands: public Hands{
    public:
        Zombie_hands();
};

typedef Zombie_hands* pZombie_hands;

#endif