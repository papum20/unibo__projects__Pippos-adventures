#include "door.hpp"


	Door::Door(Coordinate pos, Coordinate size, Coordinate entrancePosition, bool locked, bool boss) : Fixed() {
		id = ID_DOOR;
		this->pos = pos;
		this->size = size;
		this->entrancePosition = entrancePosition;
		this->locked = locked;
		this->boss = boss;
		useable = !boss;
		height = DOOR_HEIGHT;
		main_color = COLOR_DOOR;
	};


	void Door::drawAtPosition(Cell scr[CAMERA_HEIGHT][CAMERA_WIDTH], Coordinate win_start, Coordinate win_size, Coordinate pos) {
		Coordinate win_end = Coordinate(win_start, win_size);
		Coordinate i = Coordinate(pos, win_start, win_end);
		pos.setBounds(win_start, Coordinate(win_start, win_size));
		while(i.y - pos.y < height && i.y < win_end.y) {
			drawCell(scr, i, main_color);
			i.y++;
		}
	}


//// SET
	void Door::unlock() {
		locked = false;
	}
	void Door::setUseable() {
		useable = true;
	}
//// GET
	Coordinate Door::getEntrancePosition() {
		return entrancePosition;
	}
	bool Door::isLocked() {
		return locked;
	}
	bool Door::isUseable() {
		return useable;
	}
	bool Door::isBoss() {
		return boss;
	}
	