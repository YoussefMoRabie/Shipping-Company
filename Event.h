#pragma once
class Event
{
	Time ET;
	int ID;
public:
	Event(const Time& T, int id)
	{
		ID = id;
		ET = T;
	}
	virtual void Execute() = 0;
	virtual ~Event()
	{
	
	}
};