/**
 * @file PreparationEvent.h
 * @brief Children Class of Event
 * @version 0.1
 * @copyright Copyright secured by YMY Team(c) 2022
 */
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
    /**
     * @brief prepares a cargo and adds it to the right waiting list based on its type
     * 
     */
    void Execute();
};

