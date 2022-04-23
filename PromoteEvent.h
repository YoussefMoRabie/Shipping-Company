#pragma once
#include "Event.h"
class PromoteEvent :
    public Event
{
    float ExtraMoney;
public:
    PromoteEvent(Company* p, const Time&, int, float);
    void Execute();
};

