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

int Timer::get_time_passed(int timer){
	double curr_time = (double)clock() / CLOCKS_PER_SEC;
return(curr_time - timers[timer] - Total_Pauses[timer]);
}

bool Timer::check(int timer){//spegne se ha superato il tempo limite,  ritorna vero se hai superato il limite
	
		double curr_time = (double)clock() / CLOCKS_PER_SEC;
		if(curr_time-timers[timer] - Total_Pauses[timer]>max_time[timer]){
			return true;}
		else
			return false;
}
void Timer::start(int timer){//puoi riattivare un timer già attivo per resettare il suo valore
	active_timers[timer]=true;
	timers[timer]=(double)clock() / CLOCKS_PER_SEC;
}


void Timer::start_all(){
	for(int i=0; i<n_timers; i++){
		active_timers[i]=true;
		timers[i]=(double)clock() / CLOCKS_PER_SEC;
	}
}


void Timer::stop(int timer){
	active_timers[timer]=false;
	Total_Pauses[timer]=0;
}


void Timer::stop_all(){
	for(int i=0; i<n_timers; i++){
		active_timers[i]=false;
		Total_Pauses[i]=0;
	}
}


void Timer::start_pause(int timer){
	if(!State_pause[timer]){
		Start_Pause_value[timer]=(double)clock() / CLOCKS_PER_SEC;
		State_pause[timer]=true;
	}	
}


void Timer::finish_pause(int timer){
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