#ifndef FIRE_SPIRIT_HPP
#define FIRE_SPIRIT_HPP

const char fire_spirit_idle[1][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{char(39), ' ', ' ', ' '},
	{'.', ' ', char(39), ' '},
	{'_', char(39), char(39), '_'},
	{' ', ' ', ' ', ' '},
	{',', ' ', ' ', ','}
	
	}
};

const char fire_spirit_right[3][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{' ', ' ', ' ', char(39)},
	{char(39), ' ', ' ', ','},
	{'_', ')', '"', '_'},
	{' ', ' ', ' ', ' '},
	{' ', char(39), char(39), ' '}
	
	},

{
	{char(39), ' ', ' ', ' '},
	{'.', ' ', ' ', char(39)},
	{' ', ')', '"', ' '},
	{'/', ' ', ' ', '\\'},
	{',', ' ', ' ', ','}
	
	},

{
	{'.', ' ', ' ', '.'},
	{' ', ' ', ' ', '('},
	{' ', ')', '"', ' '},
	{'(', ' ', ' ', ')'},
	{' ', char(39), char(39), ' '}
	
	}
};




const char fire_spirit_left[3][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{' ', ' ', ' ', char(39)},
	{char(39), ' ', ' ', ' '},
	{'_', '"', '(', '_'},
	{' ', ' ', ' ', ' '},
	{' ', char(39), char(39), ' '}
	
	},

{
	{char(39), ' ', ' ', ' '},
	{'.', ' ', char(39), ' '},
	{' ', '"', '(', ' '},
	{'/', ' ', ' ', '\\'},
	{',', ' ', ' ', ','}
	
	},

{
	{' ', ' ', ' ', '.'},
	{')', ' ', ' ', ' '},
	{' ', '"', '(', ' '},
	{'(', ' ', ' ', ')'},
	{' ', char(39), char(39), ' '}
	
	}
};

const char fire_spirit_up[3][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{' ', ' ', ' ', char(39)},
	{char(39), ' ', ' ', ','},
	{'\\', char(39), char(39), '/'},
	{' ', ' ', ' ', ' '},
	{' ', char(39), char(39), ' '}
	
	},

{
	{' ', char(39), ' ', ' '},
	{char(39), ' ', '.', ' '},
	{' ', char(39), char(39), ' '},
	{'/', ' ', ' ', '\\'},
	{',', ' ', ' ', ','}
	
	},

{
	{' ', char(39), ' ', ' '},
	{'.', ' ', char(39), ' '},
	{' ', char(39), char(39), ' '},
	{'/', ' ', ' ', '\\'},
	{' ', char(39), char(39), ' '}
	
	}
};


const char fire_spirit_down[3][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{' ', ' ', ' ', char(39)},
	{char(39), ' ', ' ', ','},
	{'\\', char(39), char(39), '/'},
	{' ', ' ', ' ', ' '},
	{' ', char(39), char(39), ' '}
	
	},

{
	{' ', char(39), ' ', ' '},
	{char(39), ' ', '.', ' '},
	{' ', char(39), char(39), ' '},
	{'/', ' ', ' ', '\\'},
	{',', ' ', ' ', ','}
	
	},

{
	{' ', char(39), ' ', ' '},
	{'.', ' ', char(39), ' '},
	{' ', char(39), char(39), ' '},
	{'/', ' ', ' ', '\\'},
	{' ', char(39), char(39), ' '}
	
	}
};


class Fire_spirit: public Enemy{
    public:
        Fire_spirit();
};

typedef Fire_spirit* pFire_spirit;

#endif