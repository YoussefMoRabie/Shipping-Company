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
public:
	Truck(int id, TRUCK_TYPE T, int TC, float MT, int j, float S);
	TRUCK_TYPE GetType() const;
	int GetCapacity() const;
	void set_finish_point(const Time&);
	Time get_finish_point();
	float GetMaintenanceTime() const;
	float Get_nearest_dis();
	float GetSpeed() const;
	float GetDeliveryInterval();
	Time Get_nearest_stop();
	void set_nearest_stop( Time,float);
	int GetJTC();
	int GetContainer_count();
	void restore_JTC();
	void DecrementJTC();
	int GetID() const;
	void set_DInterval();
	void load(Cargo*, float delivery_time);
	Cargo* unload();
	void count_down();
	int get_move_counter();
	void Set_AT(int h);
	Time Get_AT();
	void print();
	friend ostream& operator<<(ostream& out, Truck* t);
};

