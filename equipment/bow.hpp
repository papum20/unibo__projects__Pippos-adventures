#ifndef BOW_HPP
#define BOW_HPP
#include <cstring> 
#include "../weapon.hpp"
#include "../projectiles/arrow.hpp"

const char bow_description[description_length]="arco leggendario consegnato dal dio Apollo in persona, secondo la leggenda il suo possessore non finirà mai le frecce finché lo userà per intenti puri";
const char bow_name[name_length]="Arco di Apollo";

const int bow_movement_states=1;
const int bow_attack_states_horizontal=4;
const int bow_attack_states_vertical=3;

const int bow_up_index=0;
const int bow_down_index=1;
const int bow_left_index=2;
const int bow_right_index=3;
const int bow_attack_up_index=4;
const int bow_attack_down_index=5;
const int bow_attack_left_index=6;
const int bow_attack_right_index=7;

const int bow_height=8;
const int bow_width=9;

const char bow_left[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=8 width=9

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ','/', '|', 'm', ' ', ' ', ' ', ' ', ' '},
    {' ',')', '|', '-', ' ', ' ', ' ', ' ', ' '},
	{' ','\\', '|', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	}
};

const char bow_right[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=8 width=9

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', 'm', '|', '\\', ' '},
    {' ',' ', ' ', ' ', ' ', '-', '|', '(', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', '|', '/', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	}
};


const char bow_up[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=8 width=9

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', '/', 'V', '\\', ' ', ' ', ' '},
	{' ',' ', ' ', '-', ' ', '-', ' ', ' ', ' '},
    {' ',' ', ' ', '<', '|', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	}
};

const char bow_down[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=8 width=9

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', 'm', ' ', ' ', ' '},
    {' ',' ', ' ', ' ', ' ', '>', ' ', ' ', ' '},
	{' ',' ', ' ', '-', '-', '-', ' ', ' ', ' '},
	{' ', ' ' , ' ','\\','A','/', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	}
};


const char bow_attack_right[bow_attack_states_horizontal][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=3, width=6

{   {' ',' ',' ',' ', ' ' , ' ', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ','\\',' ', ' ', ' ','/', '\\', ' '},
    {' ',' ',' ','(',' ', '-', '(', ' ', ' '},
	{' ',' ',' ','m', ' ', 'm', '\\', '/', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	},

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', '/', '\\', ' '},
	{' ',' ', ' ', '<', ' ', '-', '-', '>', ' '},
    {' ',' ', ' ', 'm', ' ', 'm', '\\', '/', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	},

{   {' ',' ',' ',' ', ' ' , ' ', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', '|', '\\', ' '},
    {' ',' ',' ',' ',' ', 'm', '|', '(', ' '},
	{' ',' ',' ',' ', ' ', '/', '|', '/', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	},

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', 'm', '|', '\\', ' '},
    {' ',' ', ' ', ' ', ' ', '-', '|', '(', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', '|', '/', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	}
};

const char bow_attack_left[bow_attack_states_horizontal][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=3, width=6

{   {' ',' ',' ',' ', ' ' , ' ', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
	{' ','/','\\',' ', ' ', ' ', '/', ' ', ' '},
    {' ',' ',')','-',' ', ')', ' ', ' ', ' '},
	{' ','\\','/','m', ' ', 'm', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	},

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ','/', '\\', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ','<', '-', '-', ' ', '>', ' ', ' ', ' '},
    {' ','\\', '/', 'm', ' ', 'm', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	},

{   {' ',' ',' ',' ', ' ' , ' ', ' ', ' ', ' '},
	{' ','/','|',' ', ' ', ' ', ' ', ' ', ' '},
	{' ',')','|',' ', ' ', ' ', ' ', ' ', ' '},
    {' ','\\','|','\\',' ', ' ', ' ', ' ', ' '},
	{' ',' ',' ','m', ' ', ' ', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	},
{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ','/', '|', 'm', ' ', ' ', ' ', ' ', ' '},
    {' ',')', '|', '-', ' ', ' ', ' ', ' ', ' '},
	{' ','\\', '|', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	}
};

const char bow_attack_up[bow_attack_states_vertical][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=8 width=9

{   {' ',' ',' ',' ', ' ' , ' ', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ',' ','/', ' ', '\\', ' ', ' ', ' '},
    {' ',' ',' ','\\',' ', '/', '/', ' ', ' '},
	{' ',' ',' ','<', ' ', ')', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	},

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', 'A', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', '/', '|', '\\', ' ', ' ', ' '},
	{' ',' ', ' ', '\\', ' ', '/', ' ', ' ', ' '},
    {' ',' ', ' ', '<', ' ','>', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	},
{   {' ',' ',' ',' ', ' ' , ' ', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ',' ','/', 'V', '\\', ' ', ' ', ' '},
    {' ',' ',' ','-',' ', '-', ' ', ' ', ' '},
	{' ',' ',' ','<', ' ', '>', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	}

};

const char bow_attack_down[bow_attack_states_vertical][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=8 width=9

{   {' ',' ',' ',' ', ' ' , ' ', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ','\\',' ', ' ', ' ', ' ', ' ', ' '},
    {' ',' ',' ','(',' ', 'm', ' ', ' ', ' '},
	{' ',' ',' ','m', ' ', '>', ' ', ' ', ' '},
	{' ',' ',' ','/', 'A', '\\', ' ', ' ', ' '},
	{' ',' ' ,' ','\\',' ','/',' ' ,' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	},

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ',' ', ' ', 'm', ' ', ' ', ' '},
    {' ',' ', ' ', ' ', ' ', '>', ' ', ' ', ' '},
	{' ',' ',' ', '/', ' ','\\',' ', ' ', ' '},
	{' ', ' ' , ' ','\\','|','/', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ','V',' ', ' ' , ' ', ' '}
	},
{   {' ',' ',' ',' ', ' ' , ' ', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
    {' ',' ',' ',' ',' ', 'm', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', '>', ' ', ' ', ' '},
	{' ',' ',' ','-', '-', '-', ' ', ' ', ' '},
	{' ', ' ' , ' ','\\','A','/', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	}
};


class Arco: public Weapon{
    protected:
    public:
		Arco();

		//pProjectile shoot();
};

#endif