/**
 * @file PromoteEvent.h
 * @brief Children Class of Event
 * @version 0.1
 * @copyright Copyright secured by YMY Team(c) 2022
 */
 */
#pragma once
#include "Event.h"
class PromoteEvent :
    public Event
{
    //money used to promote the cargo, added to its original cost
    float ExtraMoney;   
public:
    PromoteEvent(Company* p, const Time&, int, float);
    //promotes a Normal cargo to VIP given its ID
    void Execute();
};

