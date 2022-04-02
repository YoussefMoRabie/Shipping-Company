#pragma once
#include "Time.h"
#include "Company.h"

class Event
{
	Time ET;
	int ID;
protected:
	Company* cPtr;
public:
	Event(Company* p, const Time& T, int id)
	{
		cPtr = p;
		ID = id;
		ET = T;
	}
	virtual void Execute() = 0;
	virtual ~Event()
	{
	
	}
};