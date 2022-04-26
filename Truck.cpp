#include"Truck.h"
#include<iostream>
using namespace std;

Truck::Truck(TRUCK_TYPE T, int TC, float MT, int j, float S)
{
	Type = T;
	Truck_Capacity = TC;
	Maintenance_Time = MT;
	J = j;
	Speed = S;
}
TRUCK_TYPE Truck:: GetType() const
{
	return Type;
}
int Truck::GetCapacity() const
{
	return Truck_Capacity;
}
void Truck::set_DInterval(float x) {
	Delivery_Interval = x;
}

float Truck::GetMaintenanceTime() const
{
	return Maintenance_Time;
}
float Truck:: GetSpeed() const
{
	return Speed;
}
float Truck::GetDeliveryInterval()
{
	return Delivery_Interval;
}
int Truck:: GetID() const
{
	return ID;
}
ostream& operator<<(ostream& out, const Truck* t)
{
	out << t->GetID();
	return out;
}