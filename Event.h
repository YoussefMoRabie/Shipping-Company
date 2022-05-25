/**
 * @file Event.h
 * @brief Abstract class and parent of another children classes.
 * @version 0.1
 * @copyright Copyright secured by YMY Team(c) 2022
 */
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
	
	/**
	 * @brief pure virtual function, definition is different for each event class
	 * 
	 */
	virtual void Execute() = 0;
	/**
	 * @brief Get the Time object
	 * 
	 * @return Time& 
	 */
	Time& getTime()
	{
		return ET;
	}
	/**
	 * @brief Destroy the Event object
	 * 
	 */
	virtual ~Event()
	{
		delete UI_P;
	}
};