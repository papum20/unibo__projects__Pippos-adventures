#ifndef EVIL_TREE_HPP
#define EVIL_TREE_HPP

#include "../enemy.hpp"
#include "../enemy_weapons/tree_branch.hpp"

const int tree_points=100;

const int tree_width=9;
const int tree_height=6;
const int tree_depth=2;

const int tree_idle_index=0;
const int tree_move_up_index=1;
const int tree_move_down_index=2;
const int tree_move_right_index=3;
const int tree_move_left_index=4;

const int tree_idle_states=1;
const int tree_move_left_states=2;
const int tree_move_up_states=2;
const int tree_move_right_states=2;
const int tree_move_down_states=2;

const char tree_idle[tree_idle_states][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{' ','\\','|',' ',' ',' ','|','/','-'},
	{',','-','\\','o','|','o','/',char(39),' '},
	{'_',' ',' ','}','^','{',' ',' ','_'},
	{' ','\\','-','}',' ','}','-','/',' '},
	{' ',' ',' ','}',' ','{',' ',' ',' '},
	{' ',' ','/','/',' ','\\','\\',' ',' '}
	}

};

const char tree_move_left[tree_move_left_states][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{' ','\\','|',' ',' ',' ','|','/','-'},
	{',','-','\\','o','|',' ','/',char(39),' '},
	{'_',' ',' ','}','^','{',' ',' ','_'},
	{' ','\\','-','}',' ','}','-','/',' '},
	{' ',' ',' ','}',' ','{',' ',' ',' '},
	{' ',' ','/','/',' ','\\','\\',' ',' '}
	},
{
	{' ','\\','|',' ',' ',' ','|','/','-'},
	{',','-','\\','o','|',' ','/',char(39),' '},
	{' ',' ',' ','}','^','{',' ',' ','_'},
	{'_','/','-','}',' ','}','-','/',' '},
	{' ',' ',' ','}',' ','{',' ',' ',' '},
	{' ',' ',' ','/',' ','\\',' ',' ',' '}
	}

};

const char tree_move_right[tree_move_right_states][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{' ','\\','|',' ',' ',' ','|','/','-'},
	{',','-','\\',' ','|','o','/',char(39),' '},
	{'_',' ',' ','}','^','{',' ',' ','_'},
	{' ','\\','-','}',' ','}','-','/',' '},
	{' ',' ',' ','}',' ','{',' ',' ',' '},
	{' ',' ','/','/',' ','\\','\\',' ',' '}
	},
{
	{' ','\\','|',' ',' ',' ','|','/','-'},
	{',','-','\\',' ','|','o','/',char(39),' '},
	{'_',' ',' ','}','^','{',' ',' ',' '},
	{' ','\\','-','}',' ','}','-','\\','_'},
	{' ',' ',' ','}',' ','{',' ',' ',' '},
	{' ',' ',' ','/',' ','\\',' ',' ',' '}
	}

};


const char tree_move_up[tree_move_up_states][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{' ','\\','|',' ',' ',' ','|','/','-'},
	{',','-','\\',' ',' ',' ','/',char(39),' '},
	{'_',' ',' ','}',' ','{',' ',' ','_'},
	{' ','\\','-','}',' ','}','-','/',' '},
	{' ',' ',' ','}',' ','{',' ',' ',' '},
	{' ',' ','/','/',' ','\\','\\',' ',' '}
	},
{
	{' ','\\','|',' ',' ',' ','|','/','-'},
	{',','-','\\',' ',' ',' ','/',char(39),' '},
	{' ',' ',' ','}',' ','{',' ',' ',' '},
	{'_','/','-','}',' ','}','-','\\','_'},
	{' ',' ',' ','}',' ','{',' ',' ',' '},
	{' ',' ',' ','/',' ','\\',' ',' ',' '}
	}

};

const char tree_move_down[tree_move_down_states][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
{
	{' ','\\','|',' ',' ',' ','|','/','-'},
	{',','-','\\','o','|','o','/',char(39),' '},
	{'_',' ',' ','}','^','{',' ',' ','_'},
	{' ','\\','-','}',' ','}','-','/',' '},
	{' ',' ',' ','}',' ','{',' ',' ',' '},
	{' ',' ','/','/',' ','\\','\\',' ',' '}
	},
{
	{' ','\\','|',' ',' ',' ','|','/','-'},
	{',','-','\\','o','|','o','/',char(39),' '},
	{' ',' ',' ','}','^','{',' ',' ',' '},
	{'_','/','-','}',' ','}','-','\\','_'},
	{' ',' ',' ','}',' ','{',' ',' ',' '},
	{' ',' ',' ','/',' ','\\',' ',' ',' '}
	}

};

class Evil_tree: public Enemy{
    public:
		pTree_branch tree_branch;
		pArmor armatura;
		pNecklace collana;
		pBoots stivali;
		pHelm elmo;
		
        Evil_tree();
        Evil_tree(pCharacter p);
};

typedef Evil_tree* pEvil_tree;

#endif