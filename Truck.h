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
	int J;
	float Delivery_Interval; //Time to deliver all cargos & comeback, Calculated
	int ID;
	int move_counter;		//initialized with the highest load_time cargo in the container, once it reaches 0 the truck moves.
public:
	Truck(int id, TRUCK_TYPE T, int TC, float MT, int j, float S);
	TRUCK_TYPE GetType() const;
	int GetCapacity() const;

	float GetMaintenanceTime() const;
	float GetSpeed() const;
	float GetDeliveryInterval();
	int GetID() const;
	void set_DInterval(float x);
	void load(Cargo*, int LT);
	void count_down();
	int get_move_counter();
	void print();
	friend ostream& operator<<(ostream& out, const Truck* t);
};

