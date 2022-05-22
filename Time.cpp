#include "Time.h"
Time::Time(int d, int h)
{
	if (h >= 24 || h < 0)
		h = 0;
	if (d < 0)
		d = 0;
	hour = h;
	day = d;
}

Time::Time(string s)
{
	setTime(s);
}

void Time::setTime(string s)
{
	string d;
	string h;
	int i;
	for (i = 0; s[i] != ':'; i++)
		d += s[i];
	i++;
	for (int j = 0; i < s.size(); i++)
	{
		h += s[i];
		j++;
	}
	day = stoi(d);
	hour = stoi(h);
}

int Time::getDay()
{
	return day;
}

int Time::getHour()
{
	return hour;
}

int Time::Time_In_Hours()
{
	return 24 * day + hour;
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
		hour += value;
	}
}

void Time::printTime()
{
	UI_P.print(to_string(day) + ":" + to_string(hour));
}
Time Time::operator+(int value) {

	Time temp = *this;
	while (temp.hour + value >= 24)
	{
		value = value - (24 - temp.hour);
		temp.day++;
			temp.hour = 0;
	}
	temp.hour += value;
	return temp;
}

bool Time::operator==(const Time& t)
{
	if (day == t.day)
		if (hour == t.hour)
			return true;
	return false;
}
bool Time::operator>=(const Time& t)
{
	if (day > t.day)
		return true;

	if (day == t.day)
		if (hour >= t.hour)
			return true;
	return false;
}

int Time::operator-(const Time& t)
{
	return (24 * day + hour) - (24 * t.day + t.hour);
}

Time::~Time()
{

}