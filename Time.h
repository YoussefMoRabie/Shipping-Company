#pragma once
class Time
{
	int hour;
	int day;
public:
	Time(int d = 0, int h = 0);
	void AdvanceTime(int value);
	void printTime();
	int getHour();
	int getDay();
};

