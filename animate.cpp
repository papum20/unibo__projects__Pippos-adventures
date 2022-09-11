#include "animate.hpp"
#include "map_handler.hpp"


Animate::Animate() : Physical() {

}

void Animate::copyAnimate(Animate B) {
	main_color = B.main_color;

	idle_index = B.idle_index;
	
	move_up_index = B.move_up_index;
	move_down_index = B.move_down_index;
	move_left_index = B.move_left_index;
	move_right_index = B.move_right_index;
	
	attack_up_index = B.attack_up_index;
	attack_down_index = B.attack_down_index;
	attack_left_index = B.attack_left_index;
	attack_right_index = B.attack_right_index;

	direction = B.direction;
	
	copyPhysical(B);
}

attr_t Animate::get_MainColor() {
	return main_color;
}


void Animate::moveUp(pMap map){
	Coordinate movement = speed.times(REFRESH_RATE, REFRESH_RATE);
	Coordinate newpos = Coordinate(pos, DIRECTIONS[DIRECTION_UP].times(movement));
	MapHandler::move(map, this, newpos);
}

void Animate::moveDown(pMap map){
	Coordinate movement = speed.times(REFRESH_RATE, REFRESH_RATE);
	Coordinate newpos = Coordinate(pos, DIRECTIONS[DIRECTION_DOWN].times(movement));
	MapHandler::move(map, this, newpos);
}

void Animate::moveLeft(pMap map){
	Coordinate movement = speed.times(REFRESH_RATE, REFRESH_RATE);
	Coordinate newpos = Coordinate(pos, DIRECTIONS[DIRECTION_LEFT].times(movement));
	MapHandler::move(map, this, newpos);
}

void Animate::moveRight(pMap map){
	Coordinate movement = speed.times(REFRESH_RATE, REFRESH_RATE);
	Coordinate newpos = Coordinate(pos, DIRECTIONS[DIRECTION_RIGHT].times(movement));
	MapHandler::move(map, this, newpos);
}
void Animate::move(pMap map) {
	Coordinate target = nextPos(), direction = toDirection().negative();
	while(!target.equals_int(pos) && !MapHandler::move(map, this, target)) target = Coordinate(target, direction);
	lastMove = Coordinate(target, pos.negative());
	pos = target;
}


Coordinate Animate::toDirection() {
	if(direction == 'u') return DIRECTIONS[DIRECTION_UP];
	else if(direction == 'd') return DIRECTIONS[DIRECTION_DOWN];
	else if(direction == 'l') return DIRECTIONS[DIRECTION_LEFT];
	else if(direction == 'r') return DIRECTIONS[DIRECTION_RIGHT];
	else return COORDINATE_ZERO;
}


Coordinate Animate::nextPos() {
	//posizione attuale + direzione*velocità*refresh_rate
    Coordinate start = Coordinate(pos, toDirection().times(speed.times(REFRESH_RATE, REFRESH_RATE)));
	if(id==ID_PROJECTILE_S){
}
    return start;
}