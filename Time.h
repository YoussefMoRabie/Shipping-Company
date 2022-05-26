/**
 * @file Time.h
 * @brief Class responsible for time
 * @version 0.1
 * @copyright Copyright secured by YMY Team(c) 2022
 */
#pragma once
#include <string>
#include "UI.h"
using namespace std;

class Time
{
	UI * UI_P;
	int hour;
	int day;
public:
	Time();
	Time(int d , int h);
	Time(string x);
	Time(int h);
	void setTime(int h);
	void setTime(string x);
	void AdvanceTime(int value);
	void printTime();
	int getHour();
	int getDay();
	int Time_In_Hours();   //returns (24*day+hour) which is the total number of hours 
	string Time_to_print();
	bool operator==(const Time&);
	bool operator>=(const Time&);
	int operator-(const Time&);
	Time operator +(float x);
	~Time();
};

