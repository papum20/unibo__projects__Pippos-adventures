#ifndef SWORD_HPP
#define SWORD_HPP
#include <cstring>
#include "../weapon.hpp" 

const char sword_description[description_length]="forgiata da un artigiano leggendario, si dice che questa spada una volta sfoderata, non possa essere riposta senza aver preso una vita.";

const int sword_movement_states=1;
const int sword_horizontal_attack_states=4;
const int sword_vertical_attack_states=3;

const int sword_vertical_attack_animation=2;
const int sword_horizontal_attack_animation=4;

const int sword_up_index=0;
const int sword_down_index=1;
const int sword_left_index=2;
const int sword_right_index=3;
const int sword_attack_up_index=4;
const int sword_attack_down_index=5;
const int sword_attack_left_index=6;
const int sword_attack_right_index=7;

const int sword_height=8;
const int sword_width=9;

const int sword_player_x = 2;
const int sword_player_y = 1;

const int sword_horizontal_attack_width=2;
const int sword_horizontal_attack_height=1;

const int sword_vertical_attack_width=1;
const int sword_vertical_attack_height=2;


const char sword_up[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=8 width=9

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', '|', 'm', ' ', ' ', ' ', ' ', ' '},
    {' ','-', '|', '-', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	}
}; //testa comincia a destra della m la testa

const char sword_left[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=8 width=9

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', '|', 'm', ' ', ' ', ' ', ' ', ' '},
    {' ','-', '|', '-', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	}
};

const char sword_right[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=8 width=9

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', 'm', '|', ' ', ' '},
    {' ',' ', ' ', ' ', ' ', '-', '|', '-', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	}
}; //testa a sinistra della m

const char sword_down[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=8 width=9

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', 'm', ' ', ' ', ' '},
    {' ',' ', ' ', ' ', ' ', '-', '|', '-', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', '|', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	}
};

const char sword_attack_right[sword_horizontal_attack_states][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=8 width=9

{   {' ',' ',' ','\\', ' ' , ' ', ' ', ' ', ' '},
	{' ',' ',' ',' ', '\\', '/', ' ', ' ', ' '},
	{' ',' ',' ',' ', '/', '\\', ' ', ' ', ' '},
    {' ',' ',' ',' ',' ', '/', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', 'm', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	},

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ','_', '_', '|', '_', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', '|', ' ', ')', ' ', ' ', ' '},
    {' ',' ', ' ', ' ', ' ', 'm', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	},

{   {' ',' ',' ','\\', ' ' , ' ', ' ', ' ', ' '},
	{' ',' ',' ',' ', '\\', '/', ' ', ' ', ' '},
	{' ',' ',' ',' ', '/', '\\', ' ', ' ', ' '},
    {' ',' ',' ',' ',' ', '/', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', 'm', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	},

{   {' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ','_', '|', '_', '_'},
	{' ', ' ' , ' ',' ',' ','m', '|', ' ', ' '},
    {' ', ' ' , ' ',' ',' ',' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	}
};


const char sword_attack_left[sword_horizontal_attack_states][ANIMATION_HEIGHT][ANIMATION_WIDTH]={

{   {' ',' ',' ',' ', ' ' , '/', ' ', ' ', ' '},
	{' ',' ',' ','\\', '/', ' ', ' ', ' ', ' '},
	{' ',' ',' ','/', '\\', ' ', ' ', ' ', ' '},
    {' ',' ',' ','\\',' ', ' ', ' ', ' ', ' '},
	{' ',' ',' ','m', ' ', ' ', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	},

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', '_', '|', '_', '_', ' '},
	{' ',' ', ' ', '(', ' ', '|', ' ', ' ', ' '},
    {' ',' ', ' ', 'm', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	},

{   {' ',' ',' ',' ', ' ' , '/', ' ', ' ', ' '},
	{' ',' ',' ','\\', '/', ' ', ' ', ' ', ' '},
	{' ',' ',' ','/', '\\', ' ', ' ', ' ', ' '},
    {' ',' ',' ','\\',' ', ' ', ' ', ' ', ' '},
	{' ',' ',' ','m', ' ', ' ', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	},

{   {' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{'_', '_' , '|','_',' ',' ', ' ', ' ', ' '},
	{' ', ' ' , '|','m',' ',' ', ' ', ' ', ' '},
    {' ', ' ' , ' ',' ',' ',' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	}
};

const char sword_attack_up[sword_vertical_attack_states][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=8 width=9

{   {' ',' ',' ',' ', ' ' , ' ', ' ', ' ', ' '},
	{'\\',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
	{' ','\\','/',' ', ' ', ' ', ' ', ' ', ' '},
    {' ','/','\\','m',' ', ' ', ' ', ' ', ' '},
	{' ',' ',' ','-', ' ', ' ', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	},

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', '|', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', '|', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', '-', ' ', '-', ' ', ' ', ' '}, //oooo
    {' ',' ', ' ', '<', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	},

{   {' ',' ',' ',' ', ' ' , ' ', ' ', ' ', ' '},
	{'\\',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
	{' ','\\','/',' ', ' ', ' ', ' ', ' ', ' '},
    {' ','/','\\','m',' ', ' ', ' ', ' ', ' '},
	{' ',' ',' ','-', ' ', ' ', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	}

};


const char sword_attack_down[sword_vertical_attack_states][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=8 width=9

{   {' ',' ',' ',' ', ' ' , ' ', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
    {' ',' ',' ',' ',' ', 'm', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', '\\', '/', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', '\\', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , '\\', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	},

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', 'm', ' ', ' ', ' '},
    {' ',' ', ' ', ' ', ' ', '>', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', '_', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ','-','|','-', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ','|',' ', ' ' , ' ', ' '}
	},
{   {' ',' ',' ',' ', ' ' , ' ', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
    {' ',' ',' ',' ',' ', 'm', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', '\\', '/', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', '\\', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , '\\', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	}
};

class sword: public Weapon{
    protected:

    public:
		sword();
        sword (int d_f, int d_m, const char rar[], const char n[], const char desc[]);

        void apply_rune();
};

typedef sword* pSword;

#endif