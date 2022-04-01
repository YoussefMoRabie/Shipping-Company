#pragma once
#include <iostream>
#include"Def.h"
#include<string>
#include "Time.h"
using namespace std;

class Cargo
{
private:
	Time Preparation_Time; //Time(day:hour) at which the cargo is ready to be loaded
	float Load_Unload_Time;
	CARGO_TYPE Type;
	double Delivery_Distance; //Km
	double Cost;  

	public:

		Cargo(const Time& PT, float LT, CARGO_TYPE T, double DD, double C) {
			Preparation_Time = PT;
			Load_Unload_Time = LT;
			Delivery_Distance = DD;
			Type = T;
			Cost = C;
		}
		double GetDistance() {
			return Delivery_Distance;
		}
		double GetCost() {
			return Cost;
		}
		float GetLU_Time() {
			return Load_Unload_Time;
		}
		CARGO_TYPE GetType() {
			return Type;

		}
		Time& GetPrepTime() {
			return Preparation_Time;
		}
		void PromoteToVip(double ExtraMoney) {
			Type = CARGO_TYPE:: VIP;
			Cost += ExtraMoney;
		}
	




};

