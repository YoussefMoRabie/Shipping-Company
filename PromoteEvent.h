#pragma once
#include "Event.h"
class PromoteEvent :
    public Event
{
    Time ET;
    int ID;
    float ExtraMoney;
public:
    PromoteEvent(Company* p, const Time&, int, float);
    void Execute();
};

