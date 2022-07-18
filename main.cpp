#include "main.hpp"
using namespace std;




int main() {

	bool isRunning = true;
	bool isPaused = false;

	//// START: ESEGUITO UNA VOLTA ALL'AVVIO
	cursesInit();
	gameInit();
	
	//calcolo per posizionare la finestra al centro
	int stdscr_x, stdscr_y;
	getmaxyx(stdscr, stdscr_y, stdscr_x);
	int level_x = (stdscr_x - CAMERA_WIDTH) / 2, level_y = (stdscr_y - CAMERA_HEIGHT) / 2;

	//costruttori
	Player player = Player();
	Level level = Level(level_x, level_y, &player);
	Hud hud = Hud();
	InputManager inputManager = InputManager();



	//// UPDATE: ESEGUITO A OGNI FRAME
	while(isRunning)
	{
		//inputManager.getInput();

		// SE NON IN PAUSA
		if(!isPaused) {
			//player.move(inputManager.movementInput());

			level.update();
			level.display();
			//hud.drawHud();
		}
		// SE IN PAUSA
		else {
			//hud.drawHud();
		}

		// IN OGNI CASO
	}


	//// END
	cursesEnd();

}





#pragma region FUNZIONI
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
#pragma endregion FUNZIONI
