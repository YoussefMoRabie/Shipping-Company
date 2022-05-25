/**
 * @file Cargo.h
 * @brief Cargo Class
 * @version 0.1
 * @copyright Copyright secured by YMY Team(c) 2022
 */
#pragma once
#include"Def.h"
#include "Time.h"
#include <string>
#include <iostream>

class Cargo
{
private:
/**
 * @brief Time(day:hour) at which the cargo is ready to be loaded
 */
	Time Preparation_Time; 
	Time WT;
	Time DT;
	float Load_Unload_Time;
	CARGO_TYPE Type;
	/**
	 * @brief Delivery_Distance in Km
	 * 
	 */
	float Delivery_Distance;
	double Cost;
	int ID;
	int Truck_ID;

public:
/**
 * @brief Construct a new Cargo object
 * 
 * @param T 
 * @param PT 
 * @param id 
 * @param DD 
 * @param LT 
 * @param C 
 */
	Cargo(CARGO_TYPE T, const Time& PT, int id, float DD, float LT, double C);
	/**
	 * @brief Construct a new Cargo object Fake cargo just for comparison with id
	 * @param id 
	 */
	Cargo(int id); 
	/**
	 * @brief Get the Distance of cargo
	 * 
	 * @return float 
	 */
	float GetDistance() const;
	/**
	 * @brief Get the Cost of cargo
	 * 
	 * @return double 
	 */
	double GetCost() const;
	/**
	 * @brief Get the loud time of cargo
	 * 
	 * @return float 
	 */
	float GetLU_Time() const;
	/**
	 * @brief Get the Type of cargo
	 * 
	 * @return CARGO_TYPE 
	 */
	CARGO_TYPE GetType() const;
	/**
	 * @brief Get the Prep Time of cargo
	 * 
	 * @return Time& 
	 */
	Time& GetPrepTime();
	/**
	 * @brief Add Extra Money to Normal cargo when Promote To Vip
	 * 
	 * @param ExtraMoney 
	 */
	void PromoteToVip(double ExtraMoney);
	/**
	 * @brief overloading == operator 
	 * 
	 * @param ptr 
	 * @return true || false
	 */
	bool operator==(Cargo* ptr);
	/**
	 * @brief Get cargo id
	 * 
	 * @return int 
	 */
	int GetID() const;
	/**
	 * @brief Set The truck carrying the cargo ID
	 * 
	 * @param id 
	 */
	void Set_Truck_ID(int id);
	/**
	 * @brief Get The truck carrying the cargo ID
	 * @return int 
	 */
	int Get_Truck_ID();
	/**
	 * @brief Set The Delivery time
	 * 
	 * @param Time 
	 */
	void Set_DT(Time t);
	/**
	 * @brief Set The Wait time 
	 * 
	 * @param int t 
	 */
	void Set_WT(int t);
/**
 * @brief Get The Delivery time
 * 
 * @return Time& 
 */
	Time& Get_DT();
	/**
	 * @brief Get The Wait time 
	 * 
	 * @return Time& 
	 */
	Time& Get_WT();
	/**
	 * @brief Get Preparation Time
	 * 
	 * @return Time& 
	 */
	Time& Get_Preparation_Time();

	
};
/**
 * @brief overloading << operator
 *
 * @param ostream& out
 * @param Cargo* c
 * @return ostream&
 */
ostream& operator<<(ostream& out, const Cargo* c);



