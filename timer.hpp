#ifndef TIMER_HPP
#define TIMER_HPP

#include <iostream>
#include <ctime>

const int n_timers=5;

class Timer {
	protected:
		double timers[n_timers];
		bool active_timers[n_timers];
		double max_time[n_timers];
		double Start_Pause_value[n_timers];
		double Total_Pauses[n_timers];
		bool State_pause[n_timers];
		double last_frame_time;

		double current_time();
	
	public:
		Timer();
		Timer(double max_time[]);

		int get_time_passed(int timer);              //ritorna il tempo passato da quando hai fatto lo start del timer/cronometro
		bool check(int timer);		//check			//timer sarebbe la posizione dell'array che indica lo specifico cronometro	//se max<0 non ha limiti ma max è sempre maggiore di zero perchè sei tu a sceglierlo
		void start(int timer);		//starta un singolo timer(si salva il valore del clock in quel momento in timers[timer]) //consiglio di nome:	start
		void start_all();			//starta tutti i timer //consiglio di nome:	start_all
		void stop(int timer);			//stoppa un timer e quindi non è più attivo //--:					stop
		void stop_all();				//--:					stop_all
		void start_pause(int timer);		//mette in pausa un timer(rimane comunque attivo)//--:					pause
		void finish_pause(int timer);		//finisce la pausa di un timer e ritorna attivo//--:					resume

		void set_max(int timer, int val);
		bool is_active(int timer);			//true se il timer è attivo

		float deltaTime();					//tempo trascorso dall'ultimo aggiornamento
};

#endif