#ifndef AXE_HPP
#define AXE_HPP
#include <cstring> 
#include "../weapon.hpp"

const char axe_description[description_length]="arma rozza usata dal berserker, un guerriero tanto feroce da sembrare una bestia, seppur non elegante, non è seconda a nessun'altra arma in termini puro potere distruttivo.";
const char axe_name[name_length]="Ascia Berserker";

const int axe_movement_states=1;
const int axe_horizontal_attack_states=4;
const int axe_vertical_attack_states=3;

const int axe_up_index=0;
const int axe_down_index=1;
const int axe_left_index=2;
const int axe_right_index=3;
const int axe_attack_up_index=4;
const int axe_attack_down_index=5;
const int axe_attack_left_index=6;
const int axe_attack_right_index=7;

const int axe_height=8;
const int axe_width=9;

const int axe_horizontal_attack_width=3;
const int axe_horizontal_attack_height=3;

const int axe_vertical_attack_width=3;
const int axe_vertical_attack_height=3;

const int axe_vertical_attack_animation=2;
const int axe_horizontal_attack_animation=4;

const char axe_up[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=8 width=9

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ','(', '>', 'm', ' ', ' ', ' ', ' ', ' '},
    {' ',' ', '|', '-', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	}
};

const char axe_left[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=8 width=9

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ','(', '>', 'm', ' ', ' ', ' ', ' ', ' '},
    {' ',' ', '|', '-', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	}
};

const char axe_right[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=8 width=9

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', 'm', '<', ')', ' '},
    {' ',' ', ' ', ' ', ' ', '-', '|', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	}
};

const char axe_down[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=8 width=9

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', 'm', ' ', ' ', ' '},
    {' ',' ', ' ', ' ', ' ', '-', '|', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', '<', ')', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	}
};

const char axe_attack_right[axe_horizontal_attack_states][ANIMATION_HEIGHT][ANIMATION_WIDTH]={

{   {' ',' ',' ',' ', ' ' , ' ', ' ', ' ', ' '},
	{' ',' ',' ',' ', '>', ')', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', '\\', ' ', ' ', ' '},
    {' ',' ',' ',' ',' ', '/', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', 'm', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', '\\', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	},

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', '_' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', 'V', '_', '_', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ')', ' ', ' ', ' '},
    {' ',' ', ' ', ' ', ' ', 'm', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	},


{   {' ',' ',' ',' ', ' ' , ' ', ' ', ' ', ' '},
	{' ',' ',' ',' ', '>', ')', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', '\\', ' ', ' ', ' '},
    {' ',' ',' ',' ',' ', '/', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', 'm', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	},

{   {' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ','_', '_', '_', ' '},
	{' ', ' ' , ' ',' ',' ','m', '\\', '/', ' '},
    {' ', ' ' , ' ',' ',' ',' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	}
};

const char axe_attack_left[axe_horizontal_attack_states][ANIMATION_HEIGHT][ANIMATION_WIDTH]={

{   {' ',' ',' ',' ', ' ' , ' ', ' ', ' ', ' '},
	{' ',' ','(','<', ' ', ' ', ' ', ' ', ' '},
	{' ',' ',' ','/', ' ', ' ', ' ', ' ', ' '},
    {' ',' ',' ','\\',' ', ' ', ' ', ' ', ' '},
	{' ',' ',' ','m', ' ', ' ', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	},

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', '_', ' ', ' '},
	{' ',' ', ' ', ' ', '_', '_', 'V', ' ', ' '},
	{' ',' ', ' ', '(', ' ', ' ', ' ', ' ', ' '},
    {' ',' ', ' ', 'm', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	},

{   {' ',' ',' ',' ', ' ' , ' ', ' ', ' ', ' '},
	{' ',' ','(','<', ' ', ' ', ' ', ' ', ' '},
	{' ',' ',' ','/', ' ', ' ', ' ', ' ', ' '},
    {' ',' ',' ','\\',' ', ' ', ' ', ' ', ' '},
	{' ',' ',' ','m', ' ', ' ', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	},

{   {' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', '_' , '_','_',' ',' ', ' ', ' ', ' '},
	{' ', '\\' , '/','m',' ',' ', ' ', ' ', ' '},
    {' ', ' ' , ' ',' ',' ',' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	}
};

const char axe_attack_up[axe_vertical_attack_states][ANIMATION_HEIGHT][ANIMATION_WIDTH]={

{   {' ',' ',' ',' ', ' ' , ' ', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', '(', '<', ' ', ' '},
    {' ',' ',' ',' ',' ', 'm', '/', ' ', ' '},
	{' ',' ',' ',' ', ' ', '-', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	},

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', '(', '<', ' ', ' ', ' ', ' '}, //ooooo
	{' ',' ', ' ', ' ', ' ', 'm', ' ', ' ', ' '},
    {' ',' ', ' ', ' ', ' ', '>', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	},


{   {' ',' ',' ',' ', ' ' , ' ', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', '(', '<', ' ', ' '},
    {' ',' ',' ',' ',' ', 'm', '/', ' ', ' '},
	{' ',' ',' ',' ', ' ', '-', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	}
};

const char axe_attack_down[axe_vertical_attack_states][ANIMATION_HEIGHT][ANIMATION_WIDTH]={

{   {' ',' ',' ',' ', ' ' , ' ', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
    {' ',' ',' ','m',' ', ' ', ' ', ' ', ' '},
	{' ',' ',' ','/', ' ', ' ', ' ', ' ', ' '},
	{' ',' ','/',' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ','<',')',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	},

{   {' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ' ,' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', 'm', ' ', ' ', ' ', ' ', ' '},
    {' ',' ', ' ', '<', ' ', ' ', ' ', ' ', ' '},
	{' ',' ', ' ', ' ', '_', ' ', ' ', ' ', ' '},
	{' ', ' ' , ' ',' ','|',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ','<',')', ' ' , ' ', ' '}     //ooooo
	},


{   {' ',' ',' ',' ', ' ' , ' ', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
	{' ',' ',' ',' ', ' ', ' ', ' ', ' ', ' '},
    {' ',' ',' ','m',' ', ' ', ' ', ' ', ' '},
	{' ',' ',' ','/', ' ', ' ', ' ', ' ', ' '},
	{' ',' ','/',' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ','<',')',' ',' ', ' ' , ' ', ' '},
	{' ', ' ' , ' ',' ',' ',' ', ' ' , ' ', ' '}
	}
};





class Ascia: public Weapon{
    protected:

    public:
		Ascia();
        Ascia (int d_f, int d_m, const char rar[], const char n[], const char desc[]);

};

#endif