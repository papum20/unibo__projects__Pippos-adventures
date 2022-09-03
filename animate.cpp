#include "animate.hpp"


Animate::Animate() : Physical() {

}

attr_t Animate::get_MainColor() {
	return main_color;
}


void Animate::moveUp(pMap map){
    Coordinate newpos=pos;
	newpos.y--;
	MapHandler::move(map, this, newpos);
}

void Animate::moveDown(pMap map){
	Coordinate newpos=pos;
	newpos.y++;
	map->move ( this, newpos);
}

void Animate::moveLeft(pMap map){
	Coordinate newpos=pos;
	newpos.x--;
	map->move ( this, newpos);
}

void Animate::moveRight(pMap map){
	Coordinate newpos=pos;
	newpos.x++;
	map->move ( this, newpos);
}
