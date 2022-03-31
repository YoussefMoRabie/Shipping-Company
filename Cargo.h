#pragma once
#include <iostream>
#include<string>
using namespace std;
enum Cargo_Type {};
class Cargo
{
private:
	string Preparation_Time; //Time(day:hour) at which the cargo is ready to be loaded
	 
	float Load_Unload_Time;
	Cargo_Type Type;
	double Delivery_Distance; //Km
	double Cost;  

	public:

		Cargo(string, float, Cargo_Type, double, double);
		double GetDistance();
		double GetCost();
		float GetLU_Time();
		Cargo_Type GetType();
		string GetPrepTime();
		void PromoteToVip(double);
	




};

