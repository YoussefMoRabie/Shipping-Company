#pragma once
#include"Def.h"
#include "Time.h"
#include <string>

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

		Cargo(CARGO_TYPE T, const Time& PT,int id, double DD, float LT, double C) {
			Preparation_Time = PT;
			Load_Unload_Time = LT;
			Delivery_Distance = DD;
			Type = T;
			Cost = C;
			ID = id;
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
			Type = CARGO_TYPE::VIP;
			Cost += ExtraMoney;
		}
		
		bool operator==(int id)
		{
			if (this->ID == id)
				return true;
			return false;
		}
		int GetID()
		{
			return ID;
		}
		
};

