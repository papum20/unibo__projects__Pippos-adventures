#include "main.hpp"
using namespace std;




int main() {

	bool isRunning = true;
	//bool isPaused = false;

	//// START: ESEGUITO UNA VOLTA ALL'AVVIO
	cursesInit();
	gameInit();
	
	//FINESTRE
	//calcolo per posizionare la finestra di gioco al centro
	int stdscr_x, stdscr_y;
	getmaxyx(stdscr, stdscr_y, stdscr_x);
	int level_x = (stdscr_x - CAMERA_WIDTH) / 2, level_y = (stdscr_y - CAMERA_HEIGHT) / 2;
	//finestra di input (in basso a destra, sotto level)
	int input_x = level_x + CAMERA_WIDTH - input_l, input_y = level_y + CAMERA_HEIGHT;

	//costruttori
	pInputManager inputManager = new InputManager(input_x, input_y);
	Player player = Player(inputManager);
	Level level = Level(level_x, level_y, &player);
	Menu menu = Menu(inputManager);
	Hud hud = Hud(hud_window, p_max_health, p_max_stamina);

	//funzioni per la gestione input
	//keypad (input_window, true);
	//timeout(30); //millisecondi tra ogni input richiesto dalla tastiera



	//// UPDATE: ESEGUITO A OGNI FRAME
	while(isRunning)
	{
		inputManager->calculate_input();
		if (menu.is_active()) {
			if(inputManager->get_input() == KEY_PAUSE) menu.
			menu.actions(inputManager->get_input());			//se il menu è aperto il player non si muove
		}
		else {
			if(inputManager->get_input() == KEY_PAUSE) menu.open();
			//player.update(Room.map, Room.characters, inputManager.get_input()); 		//actions perchè può essere sia movimento che combattimento, poi differenzierei nella funzione
			hud.drawHud(player.curHealth, player.curStamina, player.n_hearts);
			level.update(inputManager->get_input());
			level.display();
		}
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
