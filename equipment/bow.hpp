#ifndef BOW_HPP
#define BOW_HPP
#include <cstring> 
#include "weapon.hpp"
#include "projectile.hpp"

const int bow_states = 3;

const char bow_attack_right[bow_states][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=3, width=6

{   {'\\', ' ', ' ', ' ', '/', '\\'},
	{' ', '(', ' ', '-', '(', ' ' },
	{' ', ' ', ' ', ' ', '\\', '/'}
	},

{   {' ', ' ', ' ', ' ', '/', '\\'},
	{' ', '<', ' ', '-', '-', '>' },
	{' ', ' ', ' ', ' ', '\\', '/'}
	},

{   {' ', '|', '\\', ' ', ' ', ' '},
	{' ', '|', '(', ' ', ' ', ' ' },
	{'/', '|', '/', ' ', ' ', ' '}
	}
};

const char bow_attack_left[bow_states][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=3, width=6

{   {'/', '\\', ' ', ' ', ' ', '/'},
	{' ', ')', '-', ' ', ')', ' ' },
	{'\\', '/', ' ', ' ', ' ', ' '}
	},

{   {'/', '\\', ' ', ' ', ' ', ' '},
	{'<', '-', '-', ' ', '>', ' ' },
	{'\\', '/', ' ', ' ', ' ', ' '}
	},

{   {' ', ' ', ' ', '/', '|', ' '},
	{' ', ' ', ' ', ')', '|', ' ' },
	{' ', ' ', ' ', '\\', '|', '\\'}
	}
};

const char bow_idle_right[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=3, width=3
{   {'/', '|', ' '},
	{')', '|', '-'},
	{'\\', '|', ' '}
	}
};
const char bow_idle_left[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={//height=3, width=3
{   {' ', '|', '\\'},
	{' ', '|', '('},
	{' ', '|', '/'}
	}
};

class Arco: public Weapon{
    protected:
        Projectile freccia;
    public:
        Arco (int d_f, int d_m, const char rar[]);
};

#endif