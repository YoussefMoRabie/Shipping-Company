#pragma once
#include "Event.h"
#include "Time.h"
#include "Def.h"
class PreparationEvent :
    public Event
{
    CARGO_TYPE type;
    float dist, loadTime, cost;
public:
    PreparationEvent(Company* p, CARGO_TYPE, const Time&, int, float, float, float);
    //prepares a cargo and adds it to the right waiting list based on its type
    void Execute();
};

