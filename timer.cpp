#include "timer.hpp"

Timer::Timer(double max_time[]){	
	for(int i=0; i<n_timers; i++){
		this->Total_Pauses[i]=0;
		this->max_time[i]=max_time[i];
		this->State_pause[i]=false;
	}	
};

int Timer::Check_timer(int timer){//spegne se ha superato il tempo limite, ritorna -1 error, 0 false, 1 true
if(timer<=n_timers && timer >= 0){
	double curr_time = (double)clock() / CLOCKS_PER_SEC;
	cout<<"curr_time =" << " " << curr_time<< endl << "timer = " << " " << timers[timer]<< endl;
	if(curr_time-timers[timer]>max_time[timer]){
		cout<<"controllo"<<endl;
		active_timers[timer]=false;
		return 1;}
	else
		return 0;
}
return (-1);
};
void Timer::Start_timer(int timer){//puoi riattivare un timer già attivo per resettare il suo valore
	active_timers[timer]=true;
	timers[timer]=(double)clock() / CLOCKS_PER_SEC;
};
void Timer::Start_all_timers(){
	for(int i=0; i<n_timers; i++){
		active_timers[i]=true;
		timers[i]=(double)clock() / CLOCKS_PER_SEC;
	}
};
void Timer::Stop_timer(int timer){
	active_timers[timer]=false;
};
void Timer::Stop_all_timers(){
	for(int i=0; i<n_timers; i++){
		active_timers[i]=false;
	}
};
void Timer::Start_Pause(int timer){
	if(!State_pause[timer]){
		Start_Pause_value[timer]=(double)clock() / CLOCKS_PER_SEC;
		State_pause[timer]=true;
	}	
};
void Timer::Finish_Pause(int timer){
	if(State_pause[timer]){
		double Finish_Pause=(double)clock() / CLOCKS_PER_SEC;
		Total_Pauses[timer]=Total_Pauses[timer] + (Finish_Pause - Start_Pause_value[timer]);
		State_pause[timer]=false;
	}
};
