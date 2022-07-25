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
	InputManager inputManager = InputManager(input_x, input_y);

	//funzioni per la gestione input
	keypad (input_window, true);
	timeout(30); //millisecondi tra ogni input richiesto dalla tastiera



	//// UPDATE: ESEGUITO A OGNI FRAME
	while(isRunning)
	{
		if (menu.is_open())
			menu.actions(inputManager.get_input());			//se il menu è aperto il player non si muove
		else{
			player.update(Room.map, Room.characters, inputManager.get_input()); 		//actions perchè può essere sia movimento che combattimento, poi differenzierei nella funzione
			//hud.drawHud();
		}
		level.update();
		level.display();
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
