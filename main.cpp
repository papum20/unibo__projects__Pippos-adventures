#include "main.hpp"
using namespace std;



int main() {

	bool isRunning = true;
	//bool isPaused = false;
	Timer refresh_timer = Timer();
	refresh_timer.set_max(REFRESH_TIMER_INDEX, REFRESH_RATE);

	//// START: ESEGUITO UNA VOLTA ALL'AVVIO
	cursesInit();
	gameInit();
	
	//FINESTRE
	//calcolo per posizionare la finestra di gioco al centro
	int stdscr_x, stdscr_y;
	getmaxyx(stdscr, stdscr_y, stdscr_x);
	int level_x = (stdscr_x - CAMERA_WIDTH) / 2, level_y = (stdscr_y - (CAMERA_HEIGHT + HUD_HEIGHT + HUD_OFFSET)) / 2 + HUD_HEIGHT + HUD_OFFSET;
	//finestra di input (in basso a destra, sotto level)
	int input_x = level_x + CAMERA_WIDTH, input_y = level_y + CAMERA_HEIGHT - input_h;
	//finestra hud (in alto)
	int hud_x = (stdscr_x - HUD_WIDTH) / 2, hud_y = level_y - HUD_HEIGHT - HUD_OFFSET;

	//costruttori
	pInputManager inputManager = new InputManager(input_x, input_y);
	pPlayer player = new Player(inputManager);
	Level level = Level(level_x, level_y, player);
	Menu menu = Menu(inputManager);
	Hud hud = Hud(hud_x, hud_y, player);



	WINDOW *debug = newwin(10,10,0,0);
	box(debug,0,0);
	wrefresh(debug);
	int frame = 0;
	//// UPDATE: ESEGUITO A OGNI FRAME
	while (isRunning)
	{
		
		// GESTIONE TEMPO FRAME : si eseguono tutte le operazioni, poi nel prossimo update il tempo rimasto nel tempo di aggiornamento (refresh_rate)
		// il gioco rimane "inattivo", continuando solo a ricevere l'input (comunque almeno una volta)
		while(!refresh_timer.check(REFRESH_TIMER_INDEX));
		inputManager->calculate_input();
		refresh_timer.start(REFRESH_TIMER_INDEX);

		//// IN PAUSA
		if (menu.is_active()) {
			if(frame%2==0) mvwprintw(debug,5,1,"menu");
			else mvwprintw(debug,5,1,"     ");
			//if(inputManager->get_input() == KEY_PAUSE) menu.close_menu();
		//	menu.update();			//se il menu è aperto il player non si muove
		}
		//// IN GIOCO
		else {
			if(frame%2==0) mvwprintw(debug,5,1,"level");
			else mvwprintw(debug,5,1,"     ");
			if(inputManager->get_input() == KEY_PAUSE) mvwaddch(debug,1,0,'P');// menu.open();
			else mvwaddch(debug,1,0,'p');// menu.open();
			level.update(inputManager->get_input());
			level.display();
			hud.drawHud();
		}

		mvwprintw(debug,0,0,to_string(frame).c_str());
		wrefresh(debug);
		frame++;
	}


	//// END
	cursesEnd();
	gameEnd();
	
}





#pragma region FUNZIONI
void cursesInit() {
	initscr();			//inizializza schermo ncurses
	start_color();		//inizializza colori
}
void gameInit() {
	srand(time(NULL));
	colorsInit();
}
void colorsInit() {
	Cell::initPairs();
	init_color(COLOR_BROWN, 350, 100, 90);
	init_color(COLOR_BROWN_LIGHT, 500, 150, 150);
	init_color(COLOR_GREY, 100, 90, 80);
	init_color(COLOR_GREEN, 1, 230, 1);
	//init_color(COLOR_BLUE, 2, 500, 999);
	init_color(COLOR_RED, 900, 1, 1);
}

void cursesEnd() {
	endwin();			//dealloca memoria
}
void gameEnd() {
	delete FLOOR_INSTANCE;
	delete WALL_INSTANCE;
}
#pragma endregion FUNZIONI
