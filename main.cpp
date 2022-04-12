#include "main.h"
#include "level.h"
using namespace std;




int main() {

	bool isRunning = true;
	bool isPaused = false;

	//// START: ESEGUITO UNA VOLTA ALL'AVVIO
	cursesInit();
	gameInit();

	//// UPDATE: ESEGUITO A OGNI FRAME
	while(isRunning)
	{
		// SE NON IN PAUSA
		if(!isPaused) {

		}
		// SE IN PAUSA
		else {

		}

		// IN OGNI CASO
	}


	//// END
	cursesEnd();

}








void cursesInit() {
	initscr();			//inizializza schermo ncurses
	start_color();		//inizializza colori
	curs_set(0);		//cursore invisibile
	cbreak();			//Ctrl+C esce dal gioco
}

void gameInit() {
	srand(time(NULL));
}

void cursesEnd() {
	endwin();			//dealloca memoria
}