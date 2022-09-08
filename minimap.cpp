#include "minimap.hpp"



MiniMap::MiniMap(int win_x, int win_y) {
	position = Coordinate(win_x, win_y);
	size = Coordinate(MINIMAP_WIDTH, MINIMAP_HEIGHT);
	padding = Coordinate(MINIMAP_PADDING_X, MINIMAP_PADDING_Y);
	window = newwin(size.y, size.x, win_y, win_x);
	is_open = false;
}
void MiniMap::destroy() {
	delwin(window);
}



void MiniMap::open(Level level) {
	pRoom rooms[LEVEL_AREA];
	level.getLevelMap(rooms);
	drawLevel(rooms);
	is_open = true;
}

void MiniMap::close() {
	werase(window);
	is_open = false;
}

bool MiniMap::isOpen() {
	return is_open;
}



//// DRAW
#pragma region DRAW
void MiniMap::drawLevel(pRoom rooms[LEVEL_AREA]) {
	box(window, 0, 0);
	// CERCO GLI ESTREMI DELLA MAPPA
	Coordinate mn = COORDINATE_ZERO, mx = COORDINATE_ZERO;
	Coordinate it = Coordinate(0, 0, size);
	WINDOW *w=newwin(10,10,10,0);
	do {
		if(rooms[it.single()] != NULL) {
			mvwprintw(w,1,1,to_string(rooms[it.single()]->getPos().x).c_str());
			mvwprintw(w,2,1,to_string(rooms[it.single()]->getPos().y).c_str());
			wgetch(w);
			if(it.x < mn.x) mn.x = it.x;
			else if(it.x > mx.x) mx.x = it.x;
			if(it.y < mn.y) mn.y = it.y;
			else if(it.y > mx.y) mx.y = it.y;
		}
		it.next();
	} while(!it.equals(COORDINATE_ZERO));
	wrefresh(w);
	// TROVO INFORMAZIONI
	Coordinate center = Coordinate(mn, mx).times(.5, .5).integer();									//CENTRO
	Coordinate diff = Coordinate(mx, mn.negative());												//mx-mn
	Coordinate room_size = Coordinate(size, padding.negative()).times(diff.x, diff.y).integer();	//dimensioni di una stanza
	Coordinate start = Coordinate(center, room_size.times(.5, .5).negative()).integer();			//inizio
	// ITERO SULLE STANZE E DELEGO IL DISEGNO
	it = Coordinate(mn, size, mn, mx);
	do {
		if(rooms[it.single()] != NULL) {
			Coordinate it_screen = Coordinate(it.times(room_size.x, room_size.y), start);			//converto iteratore su mappa in iteratore su schermo=it*room_size+start
			drawRoom_in_level(rooms[it.single()], it_screen, room_size);
		}
		it.next();
	} while(!it.equals(COORDINATE_ZERO));
	wrefresh(window);
}

void MiniMap::drawRoom_in_level(pRoom room, Coordinate start, Coordinate size) {
	Coordinate it = Coordinate(start, this->size, start, Coordinate(start, size));
	do {
		Cell cell;
		if(!it.inBounds(Coordinate(start, COORDINATE_ONE), Coordinate(Coordinate(start, size), COORDINATE_NEGATIVE) ) )		//se sul bordo
			cell = MINIMAP_ROOMS_BORDER;
		else if(it.equals_int(Coordinate(start, size.times(.5, .5))) )
			cell = MINIMAP_ROOMS_PLAYER;
		else cell = MINIMAP_ROOMS_EMPTY;
		mvwaddch(window, it.y, it.x, cell.toChtype());
		it.next();
	} while(!it.equals(start));
}


#pragma endregion DRAW