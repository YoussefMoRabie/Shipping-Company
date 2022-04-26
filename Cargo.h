#pragma once
#include"Def.h"
#include "Time.h"
#include <string>
#include <iostream>

class Cargo
{
private:
	Time Preparation_Time; //Time(day:hour) at which the cargo is ready to be loaded
	float Load_Unload_Time;
	CARGO_TYPE Type;
	double Delivery_Distance; //Km
	double Cost;
	int ID;

public:

	Cargo(CARGO_TYPE T, const Time& PT, int id, double DD, float LT, double C);
	Cargo(int id); //Fake cargo just for comparison with id
	double GetDistance() const;
	double GetCost() const;
	float GetLU_Time() const;
	CARGO_TYPE GetType() const;
	Time& GetPrepTime();
	void PromoteToVip(double ExtraMoney);
	bool operator==(Cargo* ptr);
	int GetID() const;
};



