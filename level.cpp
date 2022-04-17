#include "level.hpp"


Level::Level() {
	width = CAMERA_WIDTH;
	height = CAMERA_HEIGHT;

	generateMap();
}


void Level::draw() {

}


void Level::generateMap()
{
	pRoom rooms[N_ROOMS];
	for(int i = 0; i < N_ROOMS; i++) rooms[i] = NULL;
	rooms[0] = new Room();
	//genera stanze
	for(int i = 1; i < N_ROOMS; i++)
	{
		int randStart;			//stanza a cui collegare quella che verrà generata
		do {
			randStart = rand() % i;
		} while(rooms[randStart]->getSideDoors() == MAX_SIDES);
		int randRoom = rand() % (MAX_SIDES - rooms[randStart]->getSideDoors());	//direzione in cui aggiungere stanza (tra quelle ancora disponibili)
		rooms[i]->//room.nth
//probabilità uguale (albero, idee...)
	}
}