#pragma once
#include "Event.h"
class CancelEvent :
    public Event
{
public:
    CancelEvent(Company* p, const Time&, int);
    //cancels a normal cargo
    void Execute();      
};

