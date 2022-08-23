#ifndef AXE_HPP
#define AXE_HPP
#include <cstring> 
#include "weapon.hpp"

const int axe_states = 4;

const char axe_attack_right[axe_states][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=3, width=4

{   {'>', ')', ' ', ' '},
	{'\\', ' ', ' ', ' ' },
    {'/', ' ', ' ', ' ' }
	},

{   {'_', ' ', ' ', ' '},
	{'V', '_', '_', ' ' },
    {' ', ' ', ' ', ')' }
	},

{   {'>', ')', ' ', ' '},
	{'\\', ' ', ' ', ' ' },
    {'/', ' ', ' ', ' ' }
	},

{   {' ', ' ' , ' ', ' '},
	{'_', ' ', '_', '_'},
    {' ', ' ', '\\', '/' }
	}
};

const char axe_attack_left[axe_states][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=3, width=4

{   {' ', ' ', '(', ' <'},
	{' ', ' ', ' ', '/' },
    {' ', ' ', ' ', '\\' }
	},

{   {' ', ' ', ' ', '_'},
	{' ', '_', '_', 'V' },
    {'(', ' ', ' ', ' ' }
	},


{   {' ', ' ', '(', ' <'},
	{' ', ' ', ' ', '/' },
    {' ', ' ', ' ', '\\' }
	},

{   {' ', ' ' , ' ', ' '},
	{'_', '_', ' ', '_'},
    {'\\', '/', ' ', ' ' }
	}

};


const char axe_idle_left[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=2, width=3
{   {'(', '>' , ' '},
	{' ', '|', '-'} //questo non c'entra con l'animazione da combattimento dell'ascia invece è la grafica dell'ascia fuori dal combattimento    
                    //in cui hai l'ascia a sinistra e a destra lo scudo
	}
};

const char axe_idle_right[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=2, width=3
{   {' ', '<' , ')'},
	{'-', '|', ' '} //questo non c'entra con l'animazione da combattimento dell'ascia invece è la grafica dell'ascia fuori dal combattimento    
                    //in cui hai l'ascia a sinistra e a destra lo scudo
	}
};

class Ascia: public Weapon{
    protected:

    public:
        Ascia (int d_f, int d_m, const char rar[], const char n[], const char desc[]);

};

#endif