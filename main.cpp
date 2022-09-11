#include "main.hpp"
using namespace std;






int main() {

	bool isRunning = true;
	bool in_mainMenu = true;
	bool pressedPause = false;
	bool pressedMinimap = false;

	Timer game_timer = Timer();
	game_timer.set_max(REFRESH_TIMER_INDEX, REFRESH_RATE);

	//// START: ESEGUITO UNA VOLTA ALL'AVVIO
	cursesInit();
	gameInit();
	
	//FINESTRE
	//calcolo per posizionare la finestra di gioco al centro
	int stdscr_x, stdscr_y;
	getmaxyx(stdscr, stdscr_y, stdscr_x);
	int level_x = (stdscr_x - CAMERA_WIDTH) / 2, level_y = (stdscr_y - (CAMERA_HEIGHT + HUD_HEIGHT + HUD_OFFSET)) / 2 + HUD_HEIGHT + HUD_OFFSET;
	int input_x = level_x + CAMERA_WIDTH, input_y = level_y + CAMERA_HEIGHT - input_h;
	int hud_x = (stdscr_x - HUD_WIDTH) / 2, hud_y = level_y - HUD_HEIGHT - HUD_OFFSET;
	int map_x = (stdscr_x - MINIMAP_WIDTH) / 2, map_y = (stdscr_y - MINIMAP_HEIGHT) / 2;

	//costruttori
	pInputManager inputManager = new InputManager(input_x, input_y);
	System_text *text = new System_text(stdscr_x, stdscr_y);

	pPlayer player = new Player(inputManager, text);
	pLevel level = new Level(level_x, level_y, player, text);	

	Game_over *game_over = new Game_over(stdscr_x, stdscr_y, player);
	Hud *hud = new Hud(hud_x, hud_y, player);
	MiniMap *miniMap = new MiniMap(map_x, map_y, level);
	Pause_menu  *pause_menu = new Pause_menu(player,stdscr_x, stdscr_y);
	Start_menu *main_menu = new Start_menu(stdscr_x, stdscr_y);

	//// FINESTRA DI DEBUG / INFORMAZIONI
	WINDOW *debug = newwin(DEBUG_HEIGHT, DEBUG_WIDTH, DEBUG_Y, DEBUG_X);
	int frames = 0;
	game_timer.start(GAME_TIMER_INDEX);

	

	main_menu->open();
	initDebug(debug);

	
	
	//// UPDATE: ESEGUITO A OGNI FRAME
	while (isRunning)
	{
		
		// GESTIONE TEMPO FRAME : si eseguono tutte le operazioni, poi nel prossimo update il tempo rimasto nel tempo di aggiornamento (refresh_rate)
		// il gioco rimane "inattivo", continuando solo a ricevere l'input (comunque almeno una volta)
		do{
			inputManager->calculate_input();
		}while(!game_timer.check(REFRESH_TIMER_INDEX));
		game_timer.start(REFRESH_TIMER_INDEX);



		//// GESTIONE MENU APERTI CON INPUT
			// CONTROLLA SE È STATO PREMUTO UN TASTO PAUSA, MA APPLICALO SOLO SE È PRIMA STATO RILASCIATO (ALTRIMENTI IL MENU SI APRIREBBE E CHIUDEREBBE)
		if(pressedPause && inputManager->get_input() != KEY_PAUSE) pressedPause = false;
		if(pressedMinimap && inputManager->get_input() != KEY_MAP) pressedMinimap = false;

		//// MENU INIZIALE
		if(main_menu->is_active()) {
			main_menu->update(isRunning, inputManager->get_input());
		}
			// SE IL MENU INIZIALE È APPENA STATO CHIUSO
		else if(in_mainMenu) {
			level->open();
			in_mainMenu = false;
		}
		//// IN GIOCO
		else {
		//// GESTIONE MENU APERTI CON INPUT
			if(inputManager->get_input() == KEY_QUIT) isRunning = false;
			else if(inputManager->get_input() == KEY_MAIN_MENU) {
				main_menu->open_over(level);
				hud->close();
				in_mainMenu = true;
				pressedMinimap = false, pressedPause = false;
			}
			else if(inputManager->get_input() == KEY_PAUSE) {
				if(!pressedPause) {
					if (!pause_menu->is_active()) pause_menu->open();
					else level->open_over(pause_menu);
					pressedPause = true;
				}
			}
			else if(inputManager->get_input() == KEY_MAP) {
				if(!pressedMinimap) {
					if(!miniMap->isOpen()) miniMap->open();
					else level->open_over(miniMap);
					pressedMinimap = true;
				}
			}

			//// UPDATE
			if(pause_menu->is_active()) {
				if(!pressedPause) pause_menu->update(inputManager->get_input());
				else pause_menu->update(ERR);
			}
			else if(miniMap->isOpen()) {
			}
			else if(!game_over->isOpen()) {
				if(game_over->isGameOver()) {
					game_over->open();
				}
				else {
					level->update(inputManager->get_input());
					level->display();
					hud->drawHud();
					game_over->update();
				}
			}
		}


		//// DEBUG
		printDebug(debug, level->getLevel(), game_timer.get_time_passed(GAME_TIMER_INDEX), frames / game_timer.get_time_passed(GAME_TIMER_INDEX));
		frames++;
	}




	//// END
	cursesEnd();
	gameEnd();
	//DELETE
	if(!in_mainMenu) level->destroy();
	game_over->destroy();
	hud->destroy();
	inputManager->destroy();
	main_menu->destroy();
	miniMap->destroy();
	pause_menu->destroy();
	text->destroy();
	
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
	//// DELETE
	FLOOR_INSTANCE->destroy(NULL);
	WALL_INSTANCE->destroy(NULL);
}

void initDebug(WINDOW *win) {
	mvwprintw(win, DEBUG_Y_LEVEL, 0, DEBUG_WRITE_LEVEL);
	mvwprintw(win, DEBUG_Y_SECONDS, 0, DEBUG_WRITE_SECONDS);
	mvwprintw(win, DEBUG_Y_FPS, 0, DEBUG_WRITE_FPS);
	wrefresh(win);
}
void printDebug(WINDOW *win, int level, int seconds, int fps) {
	initDebug(win);
	
	char level_s[DEBUG_LENGTH], seconds_s[DEBUG_LENGTH], fps_s[DEBUG_LENGTH];
	int_to_string(level, level_s);
	int_to_string(seconds, seconds_s);
	int_to_string(fps, fps_s);
	mvwprintw(win, DEBUG_Y_LEVEL, DEBUG_X_LEVEL, level_s);
	mvwprintw(win, DEBUG_Y_SECONDS, DEBUG_X_SECONDS, seconds_s);
	mvwprintw(win, DEBUG_Y_FPS, DEBUG_X_FPS, fps_s);
	wrefresh(win);
}

int int_to_string(int n, char out[DEBUG_LENGTH]) {
	if(n < 0) return -1;
	else if(n < 10) {
		out[0] = n + 48;
		out[1] = '\0';
		return 1;
	} else {
		int len = int_to_string(n / 10, out);
		if(len < DEBUG_LENGTH - 2) {
			out[len] = (n % 10) + 48;
			out[len + 1] = '\0';
		} else if(len < DEBUG_LENGTH) out[len] = '\0';
		return len + 1;
	}
}

#pragma endregion FUNZIONI
