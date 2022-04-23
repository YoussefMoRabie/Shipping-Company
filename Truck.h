#pragma once
#include<string>
#include"Def.h"
using namespace std;

class Truck
{
private:
	TRUCK_TYPE Type;
	int Truck_Capacity; //# of cargos
	float Maintenance_Time; //hours
	float Speed; //Km/h
	float Delivery_Interval; //Time to deliver all cargos & comeback, Calculated
public:
	Truck(TRUCK_TYPE T, int TC, float MT, float S) {
		Type = T;
		Truck_Capacity = TC;
		Maintenance_Time = MT;
		
		Speed = S;
	}
	TRUCK_TYPE GetType() {
		return Type;
	}
	int GetCapacity() {
		return Truck_Capacity;
	}
	
	float GetMaintenanceTime() {
		return Maintenance_Time;
	}
	float GetSpeed() {
		return Speed;
	}
	float GetDeliveryInterval() {
		return Delivery_Interval;
	}
};

