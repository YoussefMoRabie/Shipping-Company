#pragma once
#include<string>
#include"Def.h"
#include "Cargo.h"
#include "PriQueue.h"

using namespace std;
class Truck
{
private:
	UI* ui_p;
	PriQueue<Cargo*>container;
	TRUCK_TYPE Type; 
	int Truck_Capacity; //# of cargos
	float Maintenance_Time; //hours
	float Speed; //Km/h
	int J;  // journeys untill checkup
	int Journeys_Till_Check; ////counter for journeys untill checkup
	float Delivery_Interval; //Time to deliver all cargos & comeback, Calculated
	float Delivery_Distance; //distance of the furthest cargo in container
	Time Nearest_stop; // the delivery time for the nearsest cargo
	float Nearest_dis;// distance for the nearest cargo
	int ID;
	int move_counter;	//initialized with the highest load_time cargo in the container, once it reaches 0 the truck moves.
	Time finish_point; // when the checkup finishes
	Time AT;
	int TDC;
	int N;
	Time moving_time;

public:
	Truck(int id, TRUCK_TYPE T, int TC, float MT, int j, float S);
	TRUCK_TYPE GetType() const;
	int GetCapacity() const;
	void set_finish_point(const Time&);// set the time at which the checkup finishes
	Time get_finish_point();
	float GetMaintenanceTime() const;
	float Get_nearest_dis();// gets the distance of the nearest cargo in container (top)
	float GetSpeed() const;
	float GetDeliveryInterval();
	void set_nearest_stop(Time, float); //set the nearest destination time (delivery or return)
	Time Get_nearest_stop(); 
	int GetJTC(); //get the 'journeys till checkup' counter value
	int GetContainer_count(); // gets the number of cargos in container
	void restore_JTC(); // restore 'journeys till checkup' counter with the original "J"
	void DecrementJTC(); //decrement the counter after each journey
	int GetID() const;
	void set_DInterval();
	void load(Cargo*, float delivery_time); //load cargo into conatiner
	Cargo* unload(); //unload cargo from the container
	void count_down();
	int get_move_counter();
	void Set_AT(int h);
	void inc_TDC();
	void inc_N();
	int Get_TDC();
	int Get_N();
	Time Get_AT();
	float utilization(Time& Sim_Time);
	void print_container();
	void print();
	void Set_moving_time(Time& Sim_Time);
	Time get_moving_time();
	friend ostream& operator<<(ostream& out, Truck* t);
};

