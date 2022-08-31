#include "spell.hpp"

Spell::Spell(Weapon w):Projectile(w){
    move_up_index=spell_up_index;
    move_down_index=spell_down_index;
    move_left_index=spell_left_index;
    move_right_index=spell_right_index;

    animations[move_up_index]=new Animation (spell_up, spell_width, spell_height);
    animations[move_down_index]=new Animation (spell_down, spell_width, spell_height);
    animations[move_left_index]=new Animation (spell_left, spell_width, spell_height);
    animations[move_right_index]=new Animation (spell_right, spell_width, spell_height);


}