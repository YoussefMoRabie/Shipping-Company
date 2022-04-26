#pragma once
#include<string>
#include"Def.h"
#include <string>

using namespace std;
class Truck
{
private:
	TRUCK_TYPE Type;
	int Truck_Capacity; //# of cargos
	float Maintenance_Time; //hours
	float Speed; //Km/h
	int J;
	float Delivery_Interval; //Time to deliver all cargos & comeback, Calculated
	int ID;
public:
	Truck(TRUCK_TYPE T, int TC, float MT, int j, float S);
	TRUCK_TYPE GetType() const;
	int GetCapacity() const;

	float GetMaintenanceTime() const;
	float GetSpeed() const;
	float GetDeliveryInterval();
	int GetID() const;
	void set_DInterval(float x);
	friend ostream& operator<<(ostream& out, const Truck* t);
	
};

