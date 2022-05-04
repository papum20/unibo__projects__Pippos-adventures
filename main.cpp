#include "main.hpp"
using namespace std;




int main() {

	bool isRunning = true;
	bool isPaused = false;

	//// START: ESEGUITO UNA VOLTA ALL'AVVIO
	cursesInit();
	gameInit();
	Level level = Level();
	Hud hud = Hud();
	InputManager inputManager = InputManager();
	Player player = Player();



	//// UPDATE: ESEGUITO A OGNI FRAME
	while(isRunning)
	{
		inputManager.getInput();

		// SE NON IN PAUSA
		if(!isPaused) {
			player.move(inputManager.movementInput());

			level.draw();
			hud.drawHud();
		}
		// SE IN PAUSA
		else {
			hud.drawHud();
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
