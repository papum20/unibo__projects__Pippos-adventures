#include "arrow.cpp"

Arrow::Arrow(Weapon w, p_Animation animazioni[]):Projectile(w, animazioni){
    up_width=arrow_up_width;
    up_height=arrow_up_height;

    down_width=arrow_down_width;
    down_height=arrow_down_height;
        
    right_width=arrow_right_width;
    right_height=arrow_right_height;

    left_width=arrow_left_width;
    left_height=arrow_left_height;
    
}