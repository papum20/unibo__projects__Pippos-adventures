#include "key.hpp"

Key::Key(){
}

bool Key::correct_key(int door_id){
    if (id==door_id) return true;
    else             return false;
}
