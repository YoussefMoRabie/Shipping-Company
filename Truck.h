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
	int J; //Number of delivery journeys before maintenance
	float Speed; //Km/h
	float Delivery_Interval; //Time to deliver all cargos & comeback, Calculated
public:
	Truck(TRUCK_TYPE T, int TC, float MT, int j, float S) {
		Type = T;
		Truck_Capacity = TC;
		Maintenance_Time = MT;
		J = j;
		Speed = S;
	}
	TRUCK_TYPE GetType() {
		return Type;
	}
	int GetCapacity() {
		return Truck_Capacity;
	}
	int GetJ() {
		return J;
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

