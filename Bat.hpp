#ifndef BAT_HPP
#define BAT_HPP
#include "enemy.hpp"
#include "hands.hpp"

#define Max_Health_Bat 15
#define Bat_damage 5
#define Bat_attack_ratio 1.0

const int idle_index_bat=0;
const int movement_index_bat=1;
const int idle_animation_bat_n=1;
const int movement_animation_bat_n=2;
const int bat_height=1;
const int bat_width=3;
const char idle_bat[idle_animation_bat_n][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
    {{'-', 'o', '-'}}
};
const char movement_bat[movement_animation_bat_n][ANIMATION_HEIGHT][ANIMATION_WIDTH]={
    {{'/', 'o', '\\'}} ,
    {{'\\', 'o', '/'}}
};
const Hands bat_weapon=Hands(Bat_damage, Bat_attack_ratio);

class Bat: public Enemy {
  private:
  
  protected:
    
  public:
    Bat ();
}


#endif