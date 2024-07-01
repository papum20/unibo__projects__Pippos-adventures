#include "main/minimap.hpp"



MiniMap::MiniMap(int win_x, int win_y, pLevel level) : Overlay(win_x, win_y, MINIMAP_WIDTH, MINIMAP_HEIGHT) {
	position = Coordinate(win_x, win_y);
	size = Coordinate(width, height);
	padding = Coordinate(MINIMAP_PADDING_X, MINIMAP_PADDING_Y);
	this->level = level;
	is_open = false;
}
void MiniMap::destroy() {
	Overlay::destroy();
}



void MiniMap::open() {
	pRoom rooms[LEVEL_AREA];
	level->getLevelMap(rooms);
	drawLevel(rooms, level->getSize(), level->getCurrentRoom());
	is_open = true;
}

void MiniMap::close() {
	werase(window);
	wrefresh(window);
	is_open = false;
}

bool MiniMap::isOpen() {
	return is_open;
}
void MiniMap::setLevel(pLevel level) {
	this->level = level;
}



//// DRAW
#pragma region DRAW
void MiniMap::drawLevel(pRoom rooms[LEVEL_AREA], Coordinate l_size, pRoom current) {
	box(window, 0, 0);
	// CERCO GLI ESTREMI DELLA MAPPA
	Coordinate mn = l_size, mx = COORDINATE_ZERO;
	Coordinate it = Coordinate(0, 0, l_size);
	do {
		if(rooms[it.single()] != NULL) {
			if(it.x < mn.x) mn.x = it.x;
			else if(it.x > mx.x) mx.x = it.x;
			if(it.y < mn.y) mn.y = it.y;
			else if(it.y > mx.y) mx.y = it.y;
		}
		it.next();
	} while(!it.equals(COORDINATE_ZERO));
	// TROVO INFORMAZIONI
	Coordinate diff = Coordinate(Coordinate(mx, mn.negative()), COORDINATE_ONE);										//mx-mn
	Coordinate room_size = Coordinate(size, padding.times(2, 2).negative()).times(1 / diff.x, 1 / diff.y).integer();	//dimensioni di una stanza
	Coordinate start = Coordinate(size.times(.5, .5), room_size.times(diff.x / 2, diff.y / 2).negative()).integer();	//inizio
	// ITERO SULLE STANZE E DELEGO IL DISEGNO
	it = Coordinate(mn, l_size, mn, Coordinate(mx, COORDINATE_ONE));
	do {
		if(rooms[it.single()] != NULL) {
			Coordinate it_screen = Coordinate((it.x - mn.x) * room_size.x + start.x, start.y + (mx.y - it.y) * room_size.y);
			drawRoom_in_level(rooms[it.single()], it_screen, room_size, rooms[it.single()] == current);
		}
		it.next();
	} while(!it.equals(mn));
	wrefresh(window);
}

void MiniMap::drawRoom_in_level(pRoom room, Coordinate start, Coordinate size, bool current) {
	Coordinate it = Coordinate(start, this->size, start, Coordinate(start, size));
	do {
		Cell cell;
		if(!it.inBounds(Coordinate(start, COORDINATE_ONE), Coordinate(Coordinate(start, size), COORDINATE_NEGATIVE) ) )		//se sul bordo
			cell = MINIMAP_ROOMS_BORDER;
		else if(it.equals_int(Coordinate(start, size.times(.5, .5))) ) {													//se al centro
			if(current) {
				cell = MINIMAP_ROOMS_PLAYER;																				//disegna player	
				if(room->isBossRoom()) mvwaddch(window, it.y, it.x - 1, MINIMAP_ROOMS_BOSS.toChtype());						//disegna boss
			}
			else if(room->isBossRoom()) cell = MINIMAP_ROOMS_BOSS;															//disegna boss
			else cell = MINIMAP_ROOMS_EMPTY;																				//interno
		}
		else cell = MINIMAP_ROOMS_EMPTY;																					//interno
		mvwaddch(window, it.y, it.x, cell.toChtype());
		it.next();
	} while(!it.equals(start));
}


#pragma endregion DRAW