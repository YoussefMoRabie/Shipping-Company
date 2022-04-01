#pragma once
#include "Event.h"
#include "Time.h"
class CancelEvent :
    public Event
{
public:
    CancelEvent(const Time&, int);
    void Execute();
};

