#pragma once
#include <string>
#include <sstream>
using namespace std;

class Time
{
	int hour;
	int day;
public:
	Time(int d = 0, int h = 0);
	Time(string x);
	void AdvanceTime(int value);
	void printTime();
	int getHour();
	int getDay();
};

