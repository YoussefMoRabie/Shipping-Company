#pragma once
#include "Time.h"
#include "Company.h"

class Event
{
	UI* UI_P;
	Time ET;
	int ID;
protected:
	Company* cPtr;
public:
	Event(Company* p, const Time& T, int id)
	{
		UI_P = new UI;
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