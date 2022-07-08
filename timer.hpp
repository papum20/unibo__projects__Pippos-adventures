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

		bool Check_timer(int timer);		//check			//timer sarebbe la posizione dell'array che indica lo specifico cronometro	//se max<0 non ha limiti ma max è sempre maggiore di zero perchè sei tu a sceglierlo
		void Start_timer(int timer);		//starta un singolo timer(si salva il valore del clock in quel momento in timers[timer]) //consiglio di nome:	start
		void Start_all_timers();			//starta tutti i timer //consiglio di nome:	start_all
		void Stop_timer(int timer);			//stoppa un timer e quindi non è più attivo //--:					stop
		void Stop_all_timers();				//--:					stop_all
		void Start_Pause(int timer);		//mette in pausa un timer(rimane comunque attivo)//--:					pause
		void Finish_Pause(int timer);		//finisce la pausa di un timer e ritorna attivo//--:					resume

		void set_max(int timer, int val);
		bool is_active(int timer);			//true se il timer è attivo

		float deltaTime();					//tempo trascorso dall'ultimo aggiornamento
};

#endif