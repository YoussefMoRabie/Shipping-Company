#pragma once
#include "Time.h"
#include "Company.h"

class Event
{
	UI* UI_P;

protected:
	Time ET;
	int ID;
	Company* cPtr;
public:
	Event(Company* p, const Time& T, int id)
	{
		cPtr = p;
		ID = id;
		ET = T;
	}
	virtual void Execute() = 0;
	Time& getTime()
	{
		return ET;
	}
	virtual ~Event()
	{
		delete UI_P;
	}
};