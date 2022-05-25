/**
 * @file CancelEvent.h
 * @brief cancels a normal cargo
 * @version 0.1
 * @copyright Copyright secured by YMY Team(c) 2022
 */
#pragma once
#include "Event.h"
class CancelEvent :
    public Event
{
public:
    CancelEvent(Company* p, const Time&, int);
    //cancels a Normal cargo given its ID
    void Execute();      
};

