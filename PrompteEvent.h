#pragma once
#include "Event.h"
#include "Time.h"
#include "Def.h"
class PrompteEvent :
    public Event
{
    Time ET;
    int ID;
    float ExtraMoney;
public:
    PrompteEvent(const Time&, int, float);
    void Execute();
};

