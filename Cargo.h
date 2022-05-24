#pragma once
#include"Def.h"
#include "Time.h"
#include <string>
#include <iostream>

class Cargo
{
private:
	Time Preparation_Time; //Time(day:hour) at which the cargo is ready to be loaded
	Time DT;
	Time PT;
	float Load_Unload_Time;
	CARGO_TYPE Type;
	float Delivery_Distance; //Km
	double Cost;
	int ID;
	int Truck_ID;

public:

	Cargo(CARGO_TYPE T, const Time& PT, int id, float DD, float LT, double C);
	Cargo(int id); //Fake cargo just for comparison with id
	float GetDistance() const;
	double GetCost() const;
	float GetLU_Time() const;
	CARGO_TYPE GetType() const;
	Time& GetPrepTime();
	void PromoteToVip(double ExtraMoney);
	bool operator==(Cargo* ptr);
	int GetID() const;
	void Set_Truck_ID(int id);
	int Get_Truck_ID();
	void Set_DT(Time t);
	void Set_PT(Time t);
	Time& Get_DT();
	Time& Get_PT();
	Time& Get_Preparation_Time();
	friend ostream& operator<<(ostream& out, const Cargo* c);
	
};




