#include "timer.hpp"


Timer::Timer() {
	int maxs[n_timers];
	for(int i = 0; i < n_timers; i++) maxs[i] = -1;
	Timer(maxs);
}
Timer::Timer(double max_time[]){	
	last_frame_time = clock();
	for(int i=0; i<n_timers; i++){
		this->Total_Pauses[i]=0;
		this->max_time[i]=max_time[i];
		this->State_pause[i]=false;
	}	
};

double Timer::current_time() {
	return (double)clock() / CLOCKS_PER_SEC;
}


bool Timer::Check_timer(int timer){//spegne se ha superato il tempo limite,  ritorna vero se hai superato il limite
	
		double curr_time = (double)clock() / CLOCKS_PER_SEC;
		if(curr_time-timers[timer] - Total_Pauses[timer]>max_time[timer]){
			active_timers[timer]=false;
			return true;}
		else
			return false;
}
void Timer::Start_timer(int timer){//puoi riattivare un timer già attivo per resettare il suo valore
	active_timers[timer]=true;
	timers[timer]=(double)clock() / CLOCKS_PER_SEC;
}


void Timer::Start_all_timers(){
	for(int i=0; i<n_timers; i++){
		active_timers[i]=true;
		timers[i]=(double)clock() / CLOCKS_PER_SEC;
	}
}


void Timer::Stop_timer(int timer){
	active_timers[timer]=false;
	Total_Pauses[timer]=0;
}


void Timer::Stop_all_timers(){
	for(int i=0; i<n_timers; i++){
		active_timers[i]=false;
		Total_Pauses[i]=0;
	}
}


void Timer::Start_Pause(int timer){
	if(!State_pause[timer]){
		Start_Pause_value[timer]=(double)clock() / CLOCKS_PER_SEC;
		State_pause[timer]=true;
	}	
}


void Timer::Finish_Pause(int timer){
	if(State_pause[timer]){
		double Finish_Pause=(double)clock() / CLOCKS_PER_SEC;
		Total_Pauses[timer]=Total_Pauses[timer] + (Finish_Pause - Start_Pause_value[timer]);
		State_pause[timer]=false;
	}
}


void Timer::set_max(int timer, int val) {
	if(val > 0)	max_time[timer] = val;
}
float Timer::deltaTime() {
	float current = current_time();
	float delta = current - last_frame_time;
	last_frame_time = current;
	return delta;
}