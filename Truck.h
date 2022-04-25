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
	Truck(TRUCK_TYPE T, int TC, float MT, int j, float S)
	{
		Type = T;
		Truck_Capacity = TC;
		Maintenance_Time = MT;
		J = j;
		Speed = S;
	}
	TRUCK_TYPE GetType() const
	{
		return Type;
	}
	int GetCapacity() const
	{
		return Truck_Capacity;
	}

	float GetMaintenanceTime() const
	{
		return Maintenance_Time;
	}
	float GetSpeed() const
	{
		return Speed;
	}
	float GetDeliveryInterval()
	{
		return Delivery_Interval;
	}
	int GetID() const
	{
		return ID;
	}
};

