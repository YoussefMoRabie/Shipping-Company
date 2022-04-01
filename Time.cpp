#include "Time.h"

Time::Time(int d, int h)
{
	if (hour >= 24 || h < 0)
		h = 0;
	hour = h;
	day = d;
}

int Time::getDay()
{
	return day;
}

int Time::getHour()
{
	return hour;
}

void Time::AdvanceTime(int value)
{
	if (value > 0)
	{
		while (hour + value >= 24)
		{
			value = value - (24 - hour);
			day++;
			hour = 0;
		}
		hour = value;
	}
}

void Time::printTime()
{
	//TO BE CHANGED AFTER UI IMPLEMENTATION
}
