#include "animate.hpp"


Animate::Animate() : Physical() {

}




void Physical::moveUp(pMap map){
    Coordinate newpos=pos;
	newpos.y--;
	MapHandler::move(map, this, newpos);
}

void Physical::moveDown(pMap map){
	Coordinate newpos=pos;
	newpos.y++;
	map->move ( this, newpos);
}

void Physical::moveLeft(pMap map){
	Coordinate newpos=pos;
	newpos.x--;
	map->move ( this, newpos);
}

void Physical::moveRight(pMap map){
	Coordinate newpos=pos;
	newpos.x++;
	map->move ( this, newpos);
}
