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

		int Check_timer(int timer);//timer sarebbe la posizione dell'array che indica lo specifico cronometro
		void Update_timers();

		void Start_timer(int timer);
		void Start_all_timers();
		void Start_Pause(int timer);
		void Stop_timer(int timer);
		void Stop_all_timers();
		void Finish_Pause(int timer);

		void set_max(int timer, int val);
		bool is_active(int timer);			//true se il timer è attivo

		float deltaTime();					//tempo trascorso dall'ultimo aggiornamento
};

#endif