#pragma once
#include <iostream>
#include <iostream>
#include<string>
using namespace std;
enum Truck_Type {};
class Truck
{
private:
	Truck_Type Type;
	int Truck_Capacity; //# of cargos
	float Maintenance_Time; //hours
	int J; //Number of delivery journeys before maintenance
	float Speed; //Km/h
	float Delivery_Interval; //Time to deliver all cargos & comback, Calculated
public:
	Truck(Truck_Type, int, float, int, float, float);
	Truck_Type GetType();
	int GetCapacity();
	int GetJ();
	float GetMaintenanceTime();
	float GetSpeed();
	float GetDeliveryInterval();
};

