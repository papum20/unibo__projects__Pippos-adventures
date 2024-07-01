#include "projectiles/spell.hpp"

Spell::Spell(int fisico, int magico, char dir, int shooter):Projectile(fisico, magico, dir, shooter){
    move_up_index=spell_up_index;
    move_down_index=spell_down_index;
    move_left_index=spell_left_index;
    move_right_index=spell_right_index;

    animations[move_up_index]=new Animation (spell_up, Coordinate(spell_vertical_width, spell_vertical_height));
    animations[move_down_index]=new Animation (spell_down, Coordinate(spell_vertical_width, spell_vertical_height));
    animations[move_left_index]=new Animation (spell_left, Coordinate(spell_horizontal_width, spell_horizontal_height));
    animations[move_right_index]=new Animation (spell_right, Coordinate(spell_horizontal_width, spell_horizontal_height));

    horizontal_size=Coordinate (spell_horizontal_width, spell_horizontal_height);
    vertical_size=Coordinate (spell_vertical_width,spell_vertical_height);
}