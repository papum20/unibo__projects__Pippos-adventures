#include "spell.hpp"

Spell::Spell(pWitch_rod w):Projectile(w){
    move_up_index=spell_up_index;
    move_down_index=spell_down_index;
    move_left_index=spell_left_index;
    move_right_index=spell_right_index;

    animations[move_up_index]=new Animation (spell_up, spell_vertical_width, spell_vertical_height);
    animations[move_down_index]=new Animation (spell_down, spell_vertical_width, spell_vertical_height);
    animations[move_left_index]=new Animation (spell_left, spell_horizontal_width, spell_horizontal_height);
    animations[move_right_index]=new Animation (spell_right, spell_horizontal_width, spell_horizontal_height);

    horizontal_size=Coordinate (spell_horizontal_width, spell_horizontal_height);
    vertical_size=Coordinate (spell_vertical_width,spell_vertical_height);
}

Spell::Spell(pPlayer_rod p):Projectile(p){
    move_up_index=spell_up_index;
    move_down_index=spell_down_index;
    move_left_index=spell_left_index;
    move_right_index=spell_right_index;

    animations[move_up_index]=new Animation (spell_up, spell_vertical_width, spell_vertical_height);
    animations[move_down_index]=new Animation (spell_down, spell_vertical_width, spell_vertical_height);
    animations[move_left_index]=new Animation (spell_left, spell_horizontal_width, spell_horizontal_height);
    animations[move_right_index]=new Animation (spell_right, spell_horizontal_width, spell_horizontal_height);

    horizontal_size=Coordinate (spell_horizontal_width, spell_horizontal_height);
    vertical_size=Coordinate (spell_vertical_width,spell_vertical_height);
}
    